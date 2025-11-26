package game;

import java.awt.Rectangle;

public abstract class Entity {
    protected double x;
    protected double y;
    protected double vx;
    protected double vy;
    protected int width;
    protected int height;

    public void update() {
        this.x += this.vx;
        this.y += this.vy;
    };

    Rectangle getBounds() {
        return new Rectangle((int)x, (int)y, width, height);
    }

    public double getX() {
        return this.x;
    }

    public double getY() {
        return this.y;
    }

    public int getWidth() {
        return this.width;
    }

    public int getHeight() {
        return this.height;
    }
}
