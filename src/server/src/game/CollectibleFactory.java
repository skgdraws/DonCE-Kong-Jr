package game;

/**
 * Clase abstracta que define la interfaz para crear coleccionables.
 * Implementa el patrón Factory para la creación de diferentes tipos de frutas.
 */
public abstract class CollectibleFactory {
    /**
     * Método abstracto para crear un coleccionable.
     * @return una instancia de un coleccionable específico
     */
    public abstract Collectible createCollectible();
}
