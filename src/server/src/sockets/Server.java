package sockets;

import java.io.DataInputStream;
import java.io.DataOutputStream;
import java.io.IOException;
import java.net.ServerSocket;
import java.net.Socket;
import java.util.ArrayList;

/**
 * Clase que ejecuta un servidor.
 */
public class Server {
    private ServerSocket server;
    private ArrayList<Socket> clients = new ArrayList<>();
    private ArrayList<GameClientHandler> handlers = new ArrayList<>();
    private Integer clientsIDs = 0;
    private ClientRegistrar registrar;

    /**
     * Interfaz para registrar manejadores de clientes sin acoplamiento directo.
     */
    public interface ClientRegistrar {
        void registerClientHandler(GameClientHandler handler);
        void registerSpectator(SpectatorHandler spectator, Integer gameNumber);
    }

    /**
     * Establece el registrador de clientes.
     * @param registrar implementador de ClientRegistrar
     */
    public void setClientRegistrar(ClientRegistrar registrar) {
        this.registrar = registrar;
    }

    /**
     * Función que ejecuta un servidor.
     * @throws IOException excepción
     */
    public void runServer() throws IOException {
        this.server = new ServerSocket(2121);
        newClient();
    }

    /**
     * Función que prepara a un cliente nuevo que se una al servidor.
     * @throws IOException excepción
     */
    public void newClient() throws IOException {
        while(!this.server.isClosed()){
            Socket client = this.server.accept();
            this.clients.add(client);
            assignID(client);
            
            // Leer el primer mensaje para determinar si es jugador o espectador
            try {
                DataInputStream input = new DataInputStream(client.getInputStream());
                DataOutputStream output = new DataOutputStream(client.getOutputStream());
                
                // Enviar mensaje de bienvenida
                output.writeUTF("record" + " " + ";");
                
                // Leer el primer comando del cliente
                String firstMessage = input.readUTF();
                System.out.println("Client first message: " + firstMessage);
                
                if (firstMessage.startsWith("spectate")) {
                    // Es un espectador
                    String[] tokens = firstMessage.split(" ");
                    Integer gameNumber = 1; // Default
                    if (tokens.length >= 2) {
                        try {
                            gameNumber = Integer.parseInt(tokens[1]);
                        } catch (NumberFormatException e) {
                            gameNumber = 1;
                        }
                    }
                    
                    SpectatorHandler spectator = new SpectatorHandler(client);
                    if (this.registrar != null) {
                        this.registrar.registerSpectator(spectator, gameNumber);
                    }
                } else {
                    // Es un jugador normal
                    GameClientHandler handler = new GameClientHandler(client);
                    this.handlers.add(handler);
                    
                    if (this.registrar != null) {
                        this.registrar.registerClientHandler(handler);
                    }
                    
                    // Iniciar el hilo del manejador
                    new Thread(handler).start();
                }
                
                System.out.println("Nuevo cliente conectado, es el #" + (this.clientsIDs - 1));
            } catch (IOException e) {
                System.err.println("Error creating handler for client: " + e.getMessage());
            }
        }
    }

    /**
     * Función que le asigna una identificación a un cliente
     * @param client cliente
     * @throws IOException excepción
     */
    public void assignID(Socket client) throws IOException {
        DataOutputStream outputClient = new DataOutputStream(client.getOutputStream());
        outputClient.writeUTF(String.valueOf(this.clientsIDs));
        this.clientsIDs++;
    }
}