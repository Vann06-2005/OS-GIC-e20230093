#include <arpa/inet.h>
#include <chrono>
#include <fstream>
#include <iostream>
#include <mutex>
#include <string>
#include <thread>
#include <unistd.h>

const int PORT = 9002;
const std::string FILE_NAME = "shared_score.txt";
std::mutex file_mutex;

int update_score(const std::string& name) {
    std::lock_guard<std::mutex> lock(file_mutex);

    std::ifstream input(FILE_NAME);
    int score = 0;
    input >> score;
    input.close();

    std::this_thread::sleep_for(std::chrono::milliseconds(200));

    score++;

    std::ofstream output(FILE_NAME);
    output << score << std::endl;
    output.close();

    std::cout << name << " updated score to " << score << std::endl;
    return score;
}

void handle_client(int client_socket) {
    char buffer[1024] = {0};
    read(client_socket, buffer, sizeof(buffer) - 1);

    std::string name = buffer;
    int score = update_score(name);
    std::string reply = "Score is now " + std::to_string(score) + "\n";

    send(client_socket, reply.c_str(), reply.size(), 0);
    close(client_socket);
}

int main() {
    int server_fd = socket(AF_INET, SOCK_STREAM, 0);

    int opt = 1;
    setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

    sockaddr_in address{};
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    bind(server_fd, (sockaddr*)&address, sizeof(address));
    listen(server_fd, 20);

    std::cout << "C++ mutex server running on port " << PORT << std::endl;

    while (true) {
        int client_socket = accept(server_fd, nullptr, nullptr);
        std::thread(handle_client, client_socket).detach();
    }
}
