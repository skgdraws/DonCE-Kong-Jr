package game;

/**
 * Interfaz Subject para el patrón Observer.
 * Permite agregar, remover y notificar observadores.
 */
public interface GameSubject {
    /**
     * Agrega un observador al juego.
     * @param observer observador a agregar
     */
    void addObserver(GameObserver observer);
    
    /**
     * Remueve un observador del juego.
     * @param observer observador a remover
     */
    void removeObserver(GameObserver observer);
    
    /**
     * Notifica a todos los observadores del estado actual.
     * @param gameState estado del juego a enviar
     */
    void notifyObservers(String gameState);
}
