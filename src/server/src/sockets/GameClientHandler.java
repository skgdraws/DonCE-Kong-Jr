package sockets;

import game.*;
import java.io.DataInputStream;
import java.io.DataOutputStream;
import java.io.IOException;
import java.net.Socket;

/**
 * Clase que maneja la comunicación entre un cliente y un juego específico.
 */
public class GameClientHandler implements Runnable {
    private Socket client;
    private DataOutputStream output;
    private DataInputStream input;
    private Logic game;
    private int gameNumber;
    private boolean connected = true;
    private static final String GAME_STATE_SEPARATOR = "|";

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
     * Verifica si el cliente está conectado.
     * @return true si está conectado
     */
    public boolean isConnected() {
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
     * Envía el estado actual del juego al cliente.
     */
    private void sendGameState() throws IOException {
        StringBuilder gameState = new StringBuilder();
        gameState.append("STATE").append(GAME_STATE_SEPARATOR);
        gameState.append(gameNumber).append(GAME_STATE_SEPARATOR);
        
        // Send player information
        gameState.append("PLAYER").append(GAME_STATE_SEPARATOR);
        gameState.append(game.getPlayer().getX()).append(",");
        gameState.append(game.getPlayer().getY()).append(",");
        gameState.append(game.getPlayer().getLives()).append(",");
        gameState.append(game.getPlayer().getScore()).append(",");
        gameState.append(game.getPlayer().getState()).append(GAME_STATE_SEPARATOR);
        
        // Send enemies information with type and position
        gameState.append("ENEMIES").append(GAME_STATE_SEPARATOR);
        gameState.append(buildEnemiesList()).append(GAME_STATE_SEPARATOR);
        
        // Send collectibles information with type and position
        gameState.append("FRUITS").append(GAME_STATE_SEPARATOR);
        gameState.append(buildFruitsList());
        
        this.output.writeUTF(gameState.toString());
    }

    /**
     * Construye una lista de enemigos con su tipo y posición.
     * Formato: enemy_type(x,y);enemy_type(x,y);...
     * @return string con la información de enemigos
     */
    private String buildEnemiesList() {
        StringBuilder enemies = new StringBuilder();
        java.util.ArrayList<Enemy> enemyList = game.getEnemies();
        
        for (int i = 0; i < enemyList.size(); i++) {
            Enemy enemy = enemyList.get(i);
            String type = enemy.getClass().getSimpleName().toLowerCase();
            enemies.append(type).append("(");
            enemies.append((int)enemy.getX()).append(",");
            enemies.append((int)enemy.getY()).append(")");
            
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
        
        for (int i = 0; i < collectibleList.size(); i++) {
            Collectible collectible = collectibleList.get(i);
            String type = collectible.getClass().getSimpleName().toLowerCase();
            fruits.append(type).append("(");
            fruits.append((int)collectible.getX()).append(",");
            fruits.append((int)collectible.getY()).append(")");
            
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
                
                // Enviar estado del juego al cliente
                sendGameState();
                
                // Mantener ~20 actualizaciones por segundo (50ms por frame)
                Thread.sleep(50);
                
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
    public int getGameNumber() {
        return this.gameNumber;
    }
}
