package game;

public class OrangeFactory extends CollectibleFactory {
    @Override
    public Collectible createCollectible() {
        return new Orange();
    }
}
