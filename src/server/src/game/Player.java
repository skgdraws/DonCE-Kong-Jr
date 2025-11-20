package game;

public class Player extends Entity {
    private int lives;
    protected double vx;
    protected double vy;
    protected boolean onGround;
    protected boolean climbing;

    @Override
    public void update() {
        this.x += this.vx;
        this.y += this.vy;
    }

    public void applyGravity() {
        if (!this.onGround && !this.climbing) {
            double gravity = 0.5;
            this.vy += gravity;
            double maxFallSpeed = 12;
            if (this.vy > maxFallSpeed) {
                this.vy = maxFallSpeed;
            }
        }
    }

    public void move(String direction) {
        switch (direction) {
            case "up":
                if (this.climbing) {
                    this.vy -= 0.1;
                } else  {
                    this.jump();
                }
                break;
            case "down":
                if (this.climbing) {
                    this.vy += 0.1;
                }
                break;
            case "left":
                this.vx -= 0.1;
                break;
            case "right":
                this.vx += 0.1;
                break;
            default:
                
        }
    }

    public void jump() {
        this.vy = -10;
        this.onGround = false;
    }
}
