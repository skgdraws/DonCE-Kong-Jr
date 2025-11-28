package sockets;

import java.io.DataInputStream;
import java.io.IOException;
import java.util.StringTokenizer;

public class Listener implements Runnable {
    private final DataInputStream input;
    private Boolean isReading = true;

    /**
     * Constructor de la clase.
     * @param input permite recibir contenido de un socket
     */
    public Listener(DataInputStream input) {
        this.input = input;
    }

    /**
     * Lee un mensaje del socket del servidor.
     * @return mensaje.
     * @throws IOException
     */
    public String read() throws IOException {
        String message = this.input.readUTF();
        System.out.println(message);
        return message;
    }

    /**
     * Función que ejecuta el thread para la constante escucha del socket del servidor.
     */
    public void run(){
        String message = "";
        while (isReading){
            try {
                message = read();
            } catch (IOException e) {
                this.isReading = false;
            }
        }
    }
}
