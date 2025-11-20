package game;

public class Enemy extends Entity {
    protected Vine vine;
    protected double speed;

    public Enemy (Vine vine, int level) {
        this.vine = vine;
        this.x = vine.x;
        this.y = vine.y;
        this.speed = 5 + 5 * level;

    }
    @Override
    public void update() {
        this.y += this.speed;
    }
}
