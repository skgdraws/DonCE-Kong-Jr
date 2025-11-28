package game;

/**
 * Interfaz Observer para el patrón Observer.
 * Los observadores reciben notificaciones cuando el estado del juego cambia.
 */
public interface GameObserver {
    /**
     * Llamado cuando el estado del juego se actualiza.
     * @param gameState string con el estado actual del juego
     */
    void onGameStateUpdate(String gameState);
    
    /**
     * Verifica si el observador sigue activo/conectado.
     * @return true si está activo
     */
    Boolean isActive();
}
