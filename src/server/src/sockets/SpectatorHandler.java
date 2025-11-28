package sockets;

import game.GameObserver;
import java.io.DataInputStream;
import java.io.DataOutputStream;
import java.io.IOException;
import java.net.Socket;

/**
 * Manejador de cliente espectador que implementa el patrón Observer.
 * Recibe actualizaciones del juego y las envía al cliente.
 */
public class SpectatorHandler implements GameObserver, Runnable {
    private Socket client;
    private DataOutputStream output;
    private DataInputStream input;
    private Boolean connected = true;
    private Integer gameNumber;

    /**
     * Constructor del manejador de espectador.
     * @param client socket del cliente
     * @throws IOException excepción de entrada/salida
     */
    public SpectatorHandler(Socket client) throws IOException {
        this.client = client;
        this.output = new DataOutputStream(client.getOutputStream());
        this.input = new DataInputStream(client.getInputStream());
    }

    /**
     * Establece el número de juego que está espectando.
     * @param gameNumber número del juego (1 o 2)
     */
    public void setGameNumber(Integer gameNumber) {
        this.gameNumber = gameNumber;
    }

    /**
     * Obtiene el número de juego.
     * @return número del juego
     */
    public Integer getGameNumber() {
        return this.gameNumber;
    }

    /**
     * Recibe la actualización del estado del juego y la envía al cliente.
     * Implementación del patrón Observer.
     * @param gameState estado del juego serializado
     */
    @Override
    public void onGameStateUpdate(String gameState) {
        if (!connected) return;
        
        try {
            this.output.writeUTF(gameState);
        } catch (IOException e) {
            this.connected = false;
            System.out.println("Spectator disconnected from Game " + gameNumber);
        }
    }

    /**
     * Verifica si el espectador sigue conectado.
     * @return true si está conectado
     */
    @Override
    public Boolean isActive() {
        return this.connected;
    }

    /**
     * Cierra la conexión del espectador.
     */
    public void close() {
        try {
            this.connected = false;
            this.client.close();
        } catch (IOException e) {
            System.err.println("Error closing spectator: " + e.getMessage());
        }
    }

    /**
     * Hilo que escucha comandos del espectador (solo ESC para desconectar).
     */
    @Override
    public void run() {
        System.out.println("Spectator connected to Game " + gameNumber);
        
        // Solo escuchar por si el cliente se desconecta
        while (this.connected) {
            try {
                String message = this.input.readUTF();
                // Los espectadores no pueden enviar comandos de juego
                System.out.println("Spectator sent (ignored): " + message);
            } catch (IOException e) {
                this.connected = false;
                System.out.println("Spectator disconnected from Game " + gameNumber);
            }
        }
    }
}
