package game;

/**
 * Fábrica para crear fresas coleccionables.
 * Implementa el patrón Factory para la creación de Strawberry.
 */
public class StrawberryFactory extends CollectibleFactory {
    /**
     * Crea y retorna una instancia de una fresa.
     * @return una nueva Strawberry
     */
    @Override
    public Collectible createCollectible() {
        return new Strawberry();
    }
}
