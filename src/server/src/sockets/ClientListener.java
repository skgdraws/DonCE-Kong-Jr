package sockets;

import java.io.DataInputStream;
import java.io.DataOutputStream;
import java.io.IOException;
import java.net.Socket;
import java.util.StringTokenizer;
import java.time.format.DateTimeFormatter;
import java.time.LocalDateTime;

/**
 * Clase que funciona como trabajador de un único cliente.
 */
public class ClientListener implements Runnable {
    public Socket client;
    private DataOutputStream output;
    private DataInputStream input;
    private Boolean open = true;

    /**
     * Constructor de la clase.
     * @param client cliente al que se le quiere escuchar y responder.
     * @throws IOException
     */
    public ClientListener(Socket client) throws IOException {
        this.client = client;
        this.output = new DataOutputStream(client.getOutputStream());
        this.input = new DataInputStream(client.getInputStream());
    }

    /**
     * Función que ejecuta un hilo para la constante escucha y escritura de los sockets.
     */
    public void run() {
        while (open) {
            String message = "";
            try {
                message = this.input.readUTF();
                System.out.println(">" + message);
            } catch (IOException io){
                this.open = false;
            }
        }
    }
}
