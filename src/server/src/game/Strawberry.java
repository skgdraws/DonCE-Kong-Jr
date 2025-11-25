package game;

public class Strawberry extends Collectible {
    public Strawberry(int x, int y) {
        this.x = x;
        this.y = y;
        this.vx = 0;
        this.vy = 0;
        this.width = 100;
        this.height = 100;
        this.value = 10;
    }
}
