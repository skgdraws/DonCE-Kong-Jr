package game;

public class Collectible extends Entity {
    protected int value;

    public void place (int x, int y) {
        this.x = x;
        this.y = y;
        this.vx = 0;
        this.vy = 0;
    }
}
