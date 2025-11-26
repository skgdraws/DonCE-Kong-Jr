package sockets;

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
    private int clientsIDs;
    private ClientRegistrar registrar;

    /**
     * Interfaz para registrar manejadores de clientes sin acoplamiento directo.
     */
    public interface ClientRegistrar {
        void registerClientHandler(GameClientHandler handler);
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
            DataOutputStream temp = new DataOutputStream(client.getOutputStream());
            temp.writeUTF("record" + " " + ";");
            
            // Crear manejador de cliente para juego
            try {
                GameClientHandler handler = new GameClientHandler(client);
                this.handlers.add(handler);
                
                // Registrar el manejador con la aplicación
                if (this.registrar != null) {
                    this.registrar.registerClientHandler(handler);
                }
                
                // Iniciar el hilo del manejador
                new Thread(handler).start();
                
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