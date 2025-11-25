package game;

public class RedEnemy extends Enemy {

    public RedEnemy (Vine vine, int level) {
        this.vine = vine;
        this.x = vine.x;
        this.y = vine.y;
        this.vx = 0;
        this.vy = 5 + 5 * level;
    }
    @Override
    public void patrol() {
        if (this.y + this.height > this.vine.y + this.vine.height) {
            this.vy = -this.vy;
        } else if (this.y < this.vine.y) {
            this.vy = -this.vy;
        }
    }
}
