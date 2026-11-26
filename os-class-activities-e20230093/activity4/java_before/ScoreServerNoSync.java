import java.io.*;
import java.net.*;

public class ScoreServerNoSync {
    private static final int PORT = 9011;
    private static final String FILE_NAME = "shared_score.txt";

    private static int updateScore(String name) throws Exception {
        File file = new File(FILE_NAME);
        int score = 0;

        if (file.exists()) {
            BufferedReader reader = new BufferedReader(new FileReader(file));
            String line = reader.readLine();
            reader.close();
            if (line != null && !line.isBlank()) {
                score = Integer.parseInt(line.trim());
            }
        }

        Thread.sleep(200);

        score++;

        FileWriter writer = new FileWriter(file, false);
        writer.write(score + "\n");
        writer.close();

        System.out.println(name + " updated score to " + score);
        return score;
    }

    private static void handleClient(Socket socket) {
        try {
            BufferedReader in = new BufferedReader(new InputStreamReader(socket.getInputStream()));
            PrintWriter out = new PrintWriter(socket.getOutputStream(), true);

            String name = in.readLine();
            int score = updateScore(name);
            out.println("Score is now " + score);

            socket.close();
        } catch (Exception e) {
            System.out.println("Client error: " + e.getMessage());
        }
    }

    public static void main(String[] args) throws Exception {
        ServerSocket server = new ServerSocket(PORT);
        System.out.println("Java no-sync server running on port " + PORT);

        while (true) {
            Socket socket = server.accept();
            new Thread(() -> handleClient(socket)).start();
        }
    }
}
