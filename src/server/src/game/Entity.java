package game;

import java.awt.Rectangle;

public abstract class Entity {
    protected double x;
    protected double y;
    protected int width;
    protected int height;

    abstract public void update();

    Rectangle getBounds() {
        return new Rectangle((int)x, (int)y, width, height);
    }
}
