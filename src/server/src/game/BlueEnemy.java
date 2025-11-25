package game;

public class BlueEnemy extends Enemy {

    public BlueEnemy (Vine vine, int level) {
        this.vine = vine;
        this.x = vine.x;
        this.y = vine.y;
        this.vx = 0;
        this.vy = 5 + 5 * level;
    }
    @Override
    public void patrol() {
        if (this.y + this.height > this.vine.y + this.vine.height) {
            double gravity = 0.5;
            this.vy += gravity;
            double maxFallSpeed = 12;
            if (this.vy > maxFallSpeed) {
                this.vy = maxFallSpeed;
            }
        }
    }
}
