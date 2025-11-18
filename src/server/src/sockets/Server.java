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
    private int clientsIDs;

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
            ClientListener listener = new ClientListener(client);
            new Thread(listener).start();
            System.out.println("Nuevo cliente conectado, es el #" + (this.clientsIDs - 1));
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