import game.*;
import sockets.*;
import java.io.IOException;
import java.util.Scanner;
import java.util.ArrayList;

public class App implements Server.ClientRegistrar, GameClientHandler.DisconnectCallback {
    private Logic game1; // Primera instancia del juego
    private Logic game2; // Segunda instancia del juego
    private Scanner scanner; // Escáner para entrada de usuario
    private Boolean running; // Bandera para mantener el bucle principal
    private Server server; // Servidor TCP
    private GameClientHandler handler1; // Manejador del cliente para juego 1
    private GameClientHandler handler2; // Manejador del cliente para juego 2
    private ArrayList<SpectatorHandler> spectators = new ArrayList<>(); // Lista de espectadores

    /**
     * Constructor de la clase App.
     * Inicializa dos juegos, el servidor y el escáner de entrada.
     */
    public App() {
        this.game1 = new Logic(1);
        this.game2 = new Logic(1);
        this.scanner = new Scanner(System.in);
        this.running = true;
        this.server = new Server();
    }

    /**
     * Inicia la aplicación, el servidor y el bucle de comandos.
     * Lanza el servidor en un hilo separado y muestra un menú de comandos disponibles.
     */
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
        System.out.println("  create_fruit <game> <type> <vine> <y> <value> - Create a fruit (type: banana, orange, strawberry)");
        System.out.println("  delete_fruit <game> <vineIdx> <y> - Delete a fruit at vine index with height");
        System.out.println("  status - Show game status");
        System.out.println("  exit - Exit the application");
        System.out.println();

        commandLoop();
    }

    /**
     * Bucle principal que escucha comandos del usuario.
     * Procesa comandos para crear enemigos, frutas, ver estado o salir.
     */
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
                case "delete_fruit":
                    handleDeleteFruit(tokens);
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

    /**
     * Maneja la creación de un enemigo en uno de los juegos.
     * @param tokens arreglo de tokens del comando [create_enemy, gameNum, type, vineIndex]
     */
    private void handleCreateEnemy(String[] tokens) {
        if (tokens.length < 4) {
            System.out.println("Usage: create_enemy <game> <type> <vine>");
            return;
        }

        try {
            Integer gameNum = Integer.parseInt(tokens[1]);
            String type = tokens[2].toLowerCase();
            Integer vineIndex = Integer.parseInt(tokens[3]);

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

    /**
     * Maneja la creación de una fruta en uno de los juegos.
     * @param tokens arreglo de tokens del comando [create_fruit, gameNum, type, vineIdx, y, value]
     */
    private void handleCreateFruit(String[] tokens) {
        if (tokens.length < 6) {
            System.out.println("Usage: create_fruit <game> <type> <vine> <y> <value>");
            return;
        }

        try {
            Integer gameNum = Integer.parseInt(tokens[1]);
            String type = tokens[2].toLowerCase();
            Integer vineIdx = Integer.parseInt(tokens[3]);
            Integer y = Integer.parseInt(tokens[4]);
            Integer value = Integer.parseInt(tokens[5]);

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

            targetGame.placeCollectible(factory, vineIdx, y, value);
            System.out.println("Created " + type + " on Game " + gameNum + " at vine " + vineIdx + "with height " + y + " and a value of " + value);

        } catch (NumberFormatException e) {
            System.out.println("Invalid parameters. Use: create_fruit <game> <type> <vine> <y> <value>");
        }
    }

    /**
     * Maneja la eliminación de una fruta en uno de los juegos.
     * @param tokens arreglo de tokens del comando [delete_fruit, gameNum, vineIdx, y]
     */
    private void handleDeleteFruit(String[] tokens) {
        if (tokens.length < 4) {
            System.out.println("Usage: delete_fruit <game> <vineIdx> <y>");
            return;
        }

        try {
            Integer gameNum = Integer.parseInt(tokens[1]);
            Integer vineIdx = Integer.parseInt(tokens[2]);
            Double y = Double.parseDouble(tokens[3]);

            Logic targetGame = (gameNum == 1) ? game1 : (gameNum == 2) ? game2 : null;

            if (targetGame == null) {
                System.out.println("Invalid game number. Use 1 or 2.");
                return;
            }

            targetGame.deleteCollectible(vineIdx, y);
            System.out.println("Deleted fruit on Game " + gameNum + " at vine " + vineIdx + " with height " + y);

        } catch (NumberFormatException e) {
            System.out.println("Invalid parameters. Use: delete_fruit <game> <vineIdx> <y>");
        }
    }

    /**
     * Muestra el estado actual de ambos juegos y sus clientes conectados.
     */
    private void handleStatus() {
        System.out.println("\n=== Game Status ===");
        String status1 = (handler1 != null && handler1.isConnected()) ? "Connected" : "Waiting";
        String status2 = (handler2 != null && handler2.isConnected()) ? "Connected" : "Waiting";
        System.out.println("Game 1: " + status1);
        System.out.println("Game 2: " + status2);
        System.out.println("Ready for commands...\n");
    }

    /**
     * Registra un nuevo manejador de cliente y lo asigna a uno de los dos juegos disponibles.
     * Si ambos juegos están llenos, rechaza la conexión.
     * @param handler manejador del cliente a registrar
     */
    public void registerClientHandler(GameClientHandler handler) {
        if (this.handler1 == null || !this.handler1.isConnected()) {
            this.handler1 = handler;
            handler.setGame(this.game1);
            handler.setGameNumber(1);
            handler.setDisconnectCallback(this);
            System.out.println("Client connected to Game 1 as player");
        } else if (this.handler2 == null || !this.handler2.isConnected()) {
            this.handler2 = handler;
            handler.setGame(this.game2);
            handler.setGameNumber(2);
            handler.setDisconnectCallback(this);
            System.out.println("Client connected to Game 2 as player");
        } else {
            // Ambos juegos están llenos, rechazar conexión como jugador
            System.out.println("Both games are full, rejecting player connection");
            handler.close();
        }
    }

    /**
     * Registra un espectador para un juego específico usando el patrón Observer.
     * @param spectator manejador del espectador
     * @param gameNumber número del juego a espectar (1 o 2)
     */
    public void registerSpectator(SpectatorHandler spectator, Integer gameNumber) {
        Logic targetGame = (gameNumber == 1) ? this.game1 : this.game2;
        
        // Agregar el espectador como observer del juego
        targetGame.addObserver(spectator);
        spectator.setGameNumber(gameNumber);
        this.spectators.add(spectator);
        
        // Iniciar el hilo del espectador
        new Thread(spectator).start();
        
        System.out.println("Spectator connected to Game " + gameNumber + " (Observer pattern)");
    }

    /**
     * Maneja la desconexión de un jugador, reseteando el juego para permitir nuevos jugadores.
     * Implementación de DisconnectCallback.
     * @param gameNumber número del juego del que se desconectó el jugador
     */
    @Override
    public void onPlayerDisconnect(Integer gameNumber) {
        System.out.println("Player disconnected from Game " + gameNumber + ", resetting room...");
        
        if (gameNumber == 1) {
            this.handler1 = null;
            this.game1.reset();
            System.out.println("Game 1 is now available for new players");
        } else if (gameNumber == 2) {
            this.handler2 = null;
            this.game2.reset();
            System.out.println("Game 2 is now available for new players");
        }
    }

    /**
     * Maneja el comando de salida, deteniendo la aplicación.
     */
    private void handleExit() {
        running = false;
        scanner.close();
        System.out.println("Exiting application...");
    }

    /**
     * Método principal que inicia la aplicación.
     * @param args argumentos de línea de comandos (no utilizados)
     */
    public static void main(String[] args) {
        App app = new App();
        app.start();
    }
}
