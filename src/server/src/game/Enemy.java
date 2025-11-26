package game;

import java.util.ArrayList;

public abstract class Enemy extends Entity {
    protected Vine vine;

    public void place(Vine vine) {
        this.vine = vine;
        this.x = vine.x;
        this.y = vine.y;
        this.width = 16;
        this.height = 16;
    }

    public void setLevel(int level) {
        this.vx = 0;
        this.vy = 5 + 5 * level;
    }

    public abstract void patrol();
}
