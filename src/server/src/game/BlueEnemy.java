package game;

public class BlueEnemy extends Enemy {
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
