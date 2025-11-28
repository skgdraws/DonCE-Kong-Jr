package sockets;

import game.*;
import java.io.DataInputStream;
import java.io.DataOutputStream;
import java.io.IOException;
import java.net.Socket;

/**
 * Clase que maneja la comunicación entre un cliente jugador y un juego específico.
 * Los espectadores son manejados por SpectatorHandler usando el patrón Observer.
 */
public class GameClientHandler implements Runnable {
    private Socket client;
    private DataOutputStream output;
    private DataInputStream input;
    private Logic game;
    private Integer gameNumber;
    private Boolean connected = true;
    private static final String GAME_STATE_SEPARATOR = "|";
    private DisconnectCallback disconnectCallback;

    /**
     * Interfaz para notificar cuando un jugador se desconecta.
     */
    public interface DisconnectCallback {
        void onPlayerDisconnect(Integer gameNumber);
    }

    /**
     * Constructor de la clase.
     * @param client socket del cliente
     * @throws IOException excepción de entrada/salida
     */
    public GameClientHandler(Socket client) throws IOException {
        this.client = client;
        this.output = new DataOutputStream(client.getOutputStream());
        this.input = new DataInputStream(client.getInputStream());
    }

    /**
     * Asigna el juego a este manejador.
     * @param game lógica del juego
     */
    public void setGame(Logic game) {
        this.game = game;
    }

    /**
     * Asigna el número de juego.
     * @param gameNumber número del juego (1 o 2)
     */
    public void setGameNumber(int gameNumber) {
        this.gameNumber = gameNumber;
    }

    /**
     * Asigna el callback de desconexión.
     * @param callback callback a llamar cuando el jugador se desconecte
     */
    public void setDisconnectCallback(DisconnectCallback callback) {
        this.disconnectCallback = callback;
    }

    /**
     * Verifica si el cliente está conectado.
     * @return true si está conectado
     */
    public Boolean isConnected() {
        return this.connected;
    }

    /**
     * Cierra la conexión del cliente.
     */
    public void close() {
        try {
            this.connected = false;
            this.client.close();
        } catch (IOException e) {
            System.err.println("Error closing client: " + e.getMessage());
        }
    }

    /**
     * Construye el estado actual del juego como string.
     * @return estado del juego serializado
     */
    private String buildGameState() {
        StringBuilder gameState = new StringBuilder();
        gameState.append("STATE").append(GAME_STATE_SEPARATOR);
        gameState.append(gameNumber).append(GAME_STATE_SEPARATOR);
        
        // Send player information (added facing direction)
        gameState.append("PLAYER").append(GAME_STATE_SEPARATOR);
        gameState.append(game.getPlayer().getX()).append(",");
        gameState.append(game.getPlayer().getY()).append(",");
        gameState.append(game.getPlayer().getLives()).append(",");
        gameState.append(game.getPlayer().getScore()).append(",");
        gameState.append(game.getPlayer().getState()).append(",");
        gameState.append(game.getPlayer().getFacingDirection()).append(GAME_STATE_SEPARATOR);
        
        // Send enemies information with type and position
        gameState.append("ENEMIES").append(GAME_STATE_SEPARATOR);
        gameState.append(buildEnemiesList()).append(GAME_STATE_SEPARATOR);
        
        // Send collectibles information with type and position
        gameState.append("FRUITS").append(GAME_STATE_SEPARATOR);
        gameState.append(buildFruitsList());
        
        return gameState.toString();
    }

    /**
     * Construye una lista de enemigos con su tipo, posición y dirección.
     * Formato: enemy_type(x,y,dir);enemy_type(x,y,dir);...
     * dir: "up" si vy < 0, "down" si vy >= 0
     * @return string con la información de enemigos
     */
    private String buildEnemiesList() {
        StringBuilder enemies = new StringBuilder();
        java.util.ArrayList<Enemy> enemyList = game.getEnemies();
        
        for (int i = 0; i < enemyList.size(); i++) {
            Enemy enemy = enemyList.get(i);
            String type = enemy.getClass().getSimpleName().toLowerCase();
            String direction = (enemy.getVY() < 0) ? "up" : "down";
            enemies.append(type).append("(");
            enemies.append(enemy.getX().doubleValue()).append(",");
            enemies.append(enemy.getY().doubleValue()).append(",");
            enemies.append(direction).append(")");
            
            if (i < enemyList.size() - 1) {
                enemies.append(";");
            }
        }
        
        return enemies.toString();
    }

    /**
     * Construye una lista de frutas con su tipo y posición.
     * Formato: fruit_type(x,y);fruit_type(x,y);...
     * @return string con la información de frutas
     */
    private String buildFruitsList() {
        StringBuilder fruits = new StringBuilder();
        java.util.ArrayList<Collectible> collectibleList = game.getCollectibles();
        
        for (Integer i = 0; i < collectibleList.size(); i++) {
            Collectible collectible = collectibleList.get(i);
            String type = collectible.getClass().getSimpleName().toLowerCase();
            fruits.append(type).append("(");
            fruits.append(collectible.getX().doubleValue()).append(",");
            fruits.append(collectible.getY().doubleValue()).append(")");
            
            if (i < collectibleList.size() - 1) {
                fruits.append(";");
            }
        }
        
        return fruits.toString();
    }

    /**
     * Procesa un comando de movimiento del cliente.
     * @param command comando recibido
     */
    private void processCommand(String command) {
        if (command == null || command.isEmpty()) {
            return;
        }

        String[] tokens = command.split(" ");
        String action = tokens[0].toLowerCase();

        switch (action) {
            case "move_left":
                game.getPlayer().move("left");
                break;
            case "move_right":
                game.getPlayer().move("right");
                break;
            case "jump":
                game.getPlayer().jump();
                break;
            case "climb_up":
                game.getPlayer().move("up");
                break;
            case "climb_down":
                game.getPlayer().move("down");
                break;
            case "stop":
                game.getPlayer().stop();
                break;
            default:
                System.out.println("Unknown action: " + action);
        }
    }

    /**
     * Hilo que escucha constantemente los comandos del cliente.
     */
    @Override
    public void run() {
        System.out.println("Game " + gameNumber + " handler started");
        
        // Thread separado para recibir comandos
        Thread inputThread = new Thread(() -> {
            while (this.connected) {
                try {
                    String message = this.input.readUTF();
                    System.out.println("Game " + gameNumber + " received: " + message);
                    processCommand(message);
                } catch (IOException e) {
                    this.connected = false;
                    System.out.println("Client input disconnected from Game " + gameNumber);
                }
            }
        });
        inputThread.start();
        
        // Loop principal del juego - actualiza fisica y envia estado
        while (this.connected) {
            try {
                // Actualizar fisica del juego
                game.getPlayer().applyGravity();
                game.getPlayer().update();
                
                // Actualizar enemigos
                for (Enemy enemy : game.getEnemies()) {
                    enemy.patrol();
                    enemy.update();
                }
                
                // Detectar colisiones
                game.collisions();
                
                // Construir estado del juego
                String gameState = buildGameState();
                
                // Enviar estado del juego al cliente jugador
                this.output.writeUTF(gameState);
                
                // Notificar a todos los espectadores (patrón Observer)
                game.notifyObservers(gameState);
                
                // Mantener ~30 actualizaciones por segundo (32ms por frame)
                Thread.sleep(32);
                
            } catch (IOException e) {
                this.connected = false;
                System.out.println("Client disconnected from Game " + gameNumber);
            } catch (InterruptedException e) {
                Thread.currentThread().interrupt();
                this.connected = false;
            }
        }
        
        // Esperar a que termine el thread de input
        try {
            inputThread.join(1000);
        } catch (InterruptedException e) {
            Thread.currentThread().interrupt();
        }

        // Cerrar el socket para liberar recursos
        try {
            if (!this.client.isClosed()) {
                this.client.close();
            }
        } catch (IOException e) {
            System.err.println("Error closing client socket: " + e.getMessage());
        }

        // Notificar desconexión para liberar el slot del juego
        if (this.disconnectCallback != null) {
            this.disconnectCallback.onPlayerDisconnect(this.gameNumber);
        }
        
        System.out.println("Game " + gameNumber + " handler thread terminated");
    }

    /**
     * Obtiene el juego asociado a este manejador.
     * @return el juego
     */
    public Logic getGame() {
        return this.game;
    }

    /**
     * Obtiene el número de juego.
     * @return número del juego
     */
    public Integer getGameNumber() {
        return this.gameNumber;
    }
}
