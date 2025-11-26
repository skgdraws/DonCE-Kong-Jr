import game.*;
import sockets.*;
import java.io.IOException;
import java.util.Scanner;

public class App implements Server.ClientRegistrar {
    private Logic game1;
    private Logic game2;
    private Scanner scanner;
    private boolean running;
    private Server server;
    private GameClientHandler handler1;
    private GameClientHandler handler2;

    public App() {
        this.game1 = new Logic(1);
        this.game2 = new Logic(1);
        this.scanner = new Scanner(System.in);
        this.running = true;
        this.server = new Server();
    }

    public void start() {
        System.out.println("=== Donkey Kong Jr - Multi-Game Server ===");
        System.out.println("Starting server on port 2121...");
        
        // Set this app instance as the client registrar
        this.server.setClientRegistrar(this);
        
        // Start server in a separate thread
        new Thread(() -> {
            try {
                this.server.runServer();
            } catch (IOException e) {
                System.err.println("Server error: " + e.getMessage());
            }
        }).start();
        
        System.out.println("Game 1 and Game 2 initialized with Level 1");
        System.out.println("\nAvailable commands:");
        System.out.println("  create_enemy <game> <type> <vine> - Create an enemy (type: red, blue)");
        System.out.println("  create_fruit <game> <type> <x> <y> - Create a fruit (type: banana, orange, strawberry)");
        System.out.println("  status - Show game status");
        System.out.println("  exit - Exit the application");
        System.out.println();

        commandLoop();
    }

    private void commandLoop() {
        while (running) {
            System.out.print("> ");
            String input = scanner.nextLine().trim();

            if (input.isEmpty()) {
                continue;
            }

            String[] tokens = input.split("\\s+");
            String command = tokens[0].toLowerCase();

            switch (command) {
                case "create_enemy":
                    handleCreateEnemy(tokens);
                    break;
                case "create_fruit":
                    handleCreateFruit(tokens);
                    break;
                case "status":
                    handleStatus();
                    break;
                case "exit":
                    handleExit();
                    break;
                default:
                    System.out.println("Unknown command: " + command);
            }
        }
    }

    private void handleCreateEnemy(String[] tokens) {
        if (tokens.length < 4) {
            System.out.println("Usage: create_enemy <game> <type> <vine>");
            return;
        }

        try {
            int gameNum = Integer.parseInt(tokens[1]);
            String type = tokens[2].toLowerCase();
            int vineIndex = Integer.parseInt(tokens[3]);

            Logic targetGame = (gameNum == 1) ? game1 : (gameNum == 2) ? game2 : null;

            if (targetGame == null) {
                System.out.println("Invalid game number. Use 1 or 2.");
                return;
            }

            EnemyFactory factory = null;
            if (type.equals("red")) {
                factory = new RedFactory();
            } else if (type.equals("blue")) {
                factory = new BlueFactory();
            } else {
                System.out.println("Invalid enemy type. Use 'red' or 'blue'.");
                return;
            }

            targetGame.placeEnemy(factory, vineIndex);
            System.out.println("Created " + type + " enemy on Game " + gameNum + " at vine " + vineIndex);

        } catch (NumberFormatException e) {
            System.out.println("Invalid parameters. Use: create_enemy <game> <type> <vine>");
        }
    }

    private void handleCreateFruit(String[] tokens) {
        if (tokens.length < 5) {
            System.out.println("Usage: create_fruit <game> <type> <x> <y>");
            return;
        }

        try {
            int gameNum = Integer.parseInt(tokens[1]);
            String type = tokens[2].toLowerCase();
            int x = Integer.parseInt(tokens[3]);
            int y = Integer.parseInt(tokens[4]);

            Logic targetGame = (gameNum == 1) ? game1 : (gameNum == 2) ? game2 : null;

            if (targetGame == null) {
                System.out.println("Invalid game number. Use 1 or 2.");
                return;
            }

            CollectibleFactory factory = null;
            if (type.equals("banana")) {
                factory = new BananaFactory();
            } else if (type.equals("orange")) {
                factory = new OrangeFactory();
            } else if (type.equals("strawberry")) {
                factory = new StrawberryFactory();
            } else {
                System.out.println("Invalid fruit type. Use 'banana', 'orange', or 'strawberry'.");
                return;
            }

            targetGame.placeCollectible(factory, x, y);
            System.out.println("Created " + type + " on Game " + gameNum + " at position (" + x + ", " + y + ")");

        } catch (NumberFormatException e) {
            System.out.println("Invalid parameters. Use: create_fruit <game> <type> <x> <y>");
        }
    }

    private void handleStatus() {
        System.out.println("\n=== Game Status ===");
        String status1 = (handler1 != null && handler1.isConnected()) ? "Connected" : "Waiting";
        String status2 = (handler2 != null && handler2.isConnected()) ? "Connected" : "Waiting";
        System.out.println("Game 1: " + status1);
        System.out.println("Game 2: " + status2);
        System.out.println("Ready for commands...\n");
    }

    public void registerClientHandler(GameClientHandler handler) {
        if (this.handler1 == null) {
            this.handler1 = handler;
            handler.setGame(this.game1);
            handler.setGameNumber(1);
            System.out.println("Client connected to Game 1");
        } else if (this.handler2 == null) {
            this.handler2 = handler;
            handler.setGame(this.game2);
            handler.setGameNumber(2);
            System.out.println("Client connected to Game 2");
        } else {
            System.out.println("Both games are full, rejecting client");
            handler.close();
        }
    }

    private void handleExit() {
        running = false;
        scanner.close();
        System.out.println("Exiting application...");
    }

    public static void main(String[] args) {
        App app = new App();
        app.start();
    }
}
