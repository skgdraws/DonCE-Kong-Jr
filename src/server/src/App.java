import sockets.*;

import java.io.IOException;
import java.util.Scanner;

public class App {
    public static void main(String[] args) throws IOException {
        if (args.length != 1) {
            System.err.println("Usage: java App <Mode>");
            System.exit(1);
        }
        switch (args[0]) {
            case "-c":
                Client client = new Client("a");
                client.joinServer();
                client.startClient();
                chat(client);
                break;
            case "-s":
                Server server = new Server();
                server.runServer();
                break;
            default:
                System.err.println("Usage: java App <Mode>");
                break;
        }
    }

    public static void chat(Client client) {
        String message = "";
        Scanner scanner = new Scanner(System.in);
        while (!message.equals("exit")) {
            message = scanner.nextLine();
            try {
                client.sendMessage(message);
            } catch (Exception e) {
                break;
            }
        }
    }

}
