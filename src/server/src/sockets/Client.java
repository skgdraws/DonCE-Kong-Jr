package sockets;

import java.io.DataInputStream;
import java.io.DataOutputStream;
import java.io.IOException;
import java.net.Socket;

/**
 * Clase que se conecta a un servidor y funciona como comunicador de mensajes
 */
public class Client {
    private static final Client Client = null;
    private Socket socket;
    private String id;
    private Listener reader;
    private Sender sender;

    /**
     * Constructor de la clase cliente.
     * @param tag nombre del usuario.
     * @throws IOException
     */
    public Client(String tag) throws IOException {
        joinServer();
        startClient();
        getID();
    }

    /**
     * Función que se une al servidor de sockets.
     * @throws IOException
     */
    public void joinServer() throws IOException {
        this.socket = new Socket("localhost",2121);

    }

    /**
     * Función que inicializa el lector y el escritor para los sockets.
     * @throws IOException
     */
    public void startClient() throws IOException {
        this.reader = new Listener(new DataInputStream(this.socket.getInputStream()));
        this.sender = new Sender(new DataOutputStream(this.socket.getOutputStream()));
    }

    /**
     * Función que obtiene una identificación para el cliente.
     * @throws IOException
     */
    public void getID() throws IOException {
        DataInputStream input = new DataInputStream(this.socket.getInputStream());
        this.id = input.readUTF();
        new Thread(this.reader).start();
        System.out.println("ID de cliente: " + this.id);
    }

    /**
     * Función que envía un mensaje hacia el socket del servidor.
     * @param message mensaje.
     * @throws IOException
     */
    public void sendMessage(String message) throws IOException {
        this.sender.startSender(message);
    }
}
