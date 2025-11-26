package sockets;

import java.io.DataOutputStream;
import java.io.IOException;

public class Sender {
    private final DataOutputStream output;

    /**
     * Constructor para colocar la salida para los mensajes.
     * @param output permite enviar contenido de un socket
     */
    public Sender (DataOutputStream output) {
        this.output = output;
    }

    /**
     * Función que envía un mensaje.
     * @param message texto del mensaje.
     * @throws IOException detecta excepciones de E/S
     */
    public void startSender(String message) throws IOException {
        this.output.writeUTF(message);
    }

    /**
     * Función que envía mensajes a un determinado socket.
     * @param message mensaje enviado.
     * @param socketTO cliente al que se quiere comunicar.
     * @throws IOException excepción.
     */
    public void startSender(String message, DataOutputStream socketTO) throws IOException {
        socketTO.writeUTF(message);
    }

}
