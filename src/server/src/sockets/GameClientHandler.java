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
        gameState.append(game.getPlayer().x).append(",");
        gameState.append(game.getPlayer().y).append(",");
        gameState.append(game.getPlayer().lives).append(",");
        gameState.append(game.getPlayer().score).append(GAME_STATE_SEPARATOR);
        
        // Send enemies information
        gameState.append("ENEMIES").append(GAME_STATE_SEPARATOR);
        gameState.append(game.getEnemies().size()).append(GAME_STATE_SEPARATOR);
        
        // Send collectibles information
        gameState.append("COLLECTIBLES").append(GAME_STATE_SEPARATOR);
        gameState.append(game.getCollectibles().size());
        
        this.output.writeUTF(gameState.toString());
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
        
        while (this.connected) {
            try {
                // Enviar estado del juego
                sendGameState();
                
                // Recibir comando del cliente
                String message = this.input.readUTF();
                System.out.println("Game " + gameNumber + " received: " + message);
                
                // Procesar comando
                processCommand(message);
                
                // Pequeña pausa para no saturar
                Thread.sleep(50);
                
            } catch (IOException e) {
                this.connected = false;
                System.out.println("Client disconnected from Game " + gameNumber);
            } catch (InterruptedException e) {
                Thread.currentThread().interrupt();
                this.connected = false;
            }
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
