package game;

import java.lang.Math;

public class Player extends Entity {
    protected int lives;
    protected int score;
    protected boolean onGround;
    protected boolean climbing;

    public Player() {
        this.lives = 3;
        this.score = 0;
        this.onGround = false;
        this.climbing = false;
        this.width = 32;
        this.height = 16;
        this.vx = 0.0;
        this.vy = 0.0;
    }

    public double getX() {
        return this.x;
    }

    public double getY() {
        return this.y;
    }

    public int getLives() {
        return this.lives;
    }

    public int getScore() {
        return this.score;
    }

    public String getState() {
        if (this.climbing) {
            return "climbing";
        } else if (Math.abs(this.vx) > 0.5) {
            return "walking";
        } else {
            return "idle";
        }
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

    public void jump() {
        if (this.onGround) {
            this.vy = -10;
            this.onGround = false;
        }
    }

    public void stop() {
        // Apply friction to slow down
        if (Math.abs(this.vx) < 0.5) {
            this.vx = 0;
        } else if (this.vx < 0) {
            this.vx += 0.5;
        } else if (this.vx > 0) {
            this.vx -= 0.5;
        }
    }

    public void move(String direction) {
        int maxSpeed = 9;
        int maxClimbSpeed = 6;
        switch (direction) {
            case "up":
                if (this.climbing) {
                    this.vy -= 3;
                    if (Math.abs(this.vy) > maxClimbSpeed) {
                        this.vy = -maxSpeed;
                    }
                } else {
                    this.jump();
                }
                break;
            case "down":
                if (this.climbing) {
                    this.vy += 3;
                    if (this.vy > maxClimbSpeed) {
                        this.vy = maxClimbSpeed;
                    }
                }
                break;
            case "left":
                this.vx -= 3;
                if (Math.abs(this.vx) > maxSpeed) {
                    this.vx = -maxSpeed;
                }
                break;
            case "right":
                this.vx += 3;
                if (this.vx > maxSpeed) {
                    this.vx = maxSpeed;
                }
                break;
            default:
                this.stop();
                break;
        }
    }
}
