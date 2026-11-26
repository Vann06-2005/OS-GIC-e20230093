import java.io.*;
import java.net.*;

public class ScoreClient {
    private static final int PORT = 9011;

    public static void main(String[] args) throws Exception {
        if (args.length < 2) {
            System.out.println("Usage: java ScoreClient <server_ip> <student_name>");
            return;
        }

        String serverIp = args[0];
        String name = args[1];

        Socket socket = new Socket(serverIp, PORT);
        BufferedReader in = new BufferedReader(new InputStreamReader(socket.getInputStream()));
        PrintWriter out = new PrintWriter(socket.getOutputStream(), true);

        out.println(name);
        System.out.println(in.readLine());

        socket.close();
    }
}
