package game;

public class BananaFactory extends CollectibleFactory {
    @Override
    public Collectible createCollectible() {
        return new Banana();
    }
}
