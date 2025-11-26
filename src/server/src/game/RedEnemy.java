package game;

public class RedEnemy extends Enemy {
    @Override
    public void patrol() {
        if (this.y + this.height > this.vine.y + this.vine.height) {
            this.vy = -this.vy;
        } else if (this.y < this.vine.y) {
            this.vy = -this.vy;
        }
    }
}
