package game;

/**
 * Fábrica para crear bananas coleccionables.
 * Implementa el patrón Factory para la creación de Banana.
 */
public class BananaFactory extends CollectibleFactory {
    /**
     * Crea y retorna una instancia de una banana.
     * @return una nueva Banana
     */
    @Override
    public Collectible createCollectible() {
        return new Banana();
    }
}
