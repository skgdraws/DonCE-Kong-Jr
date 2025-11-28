package game;

/**
 * Fábrica para crear naranjas coleccionables.
 * Implementa el patrón Factory para la creación de Orange.
 */
public class OrangeFactory extends CollectibleFactory {
    /**
     * Crea y retorna una instancia de una naranja.
     * @return una nueva Orange
     */
    @Override
    public Collectible createCollectible() {
        return new Orange();
    }
}
