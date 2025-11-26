package game;

public class StrawberryFactory extends CollectibleFactory {
    @Override
    public Collectible createCollectible() {
        return new Strawberry();
    }
}
