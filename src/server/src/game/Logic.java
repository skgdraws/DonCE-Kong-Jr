package game;

import java.awt.*;
import java.util.ArrayList;

public class Logic {
    private int level;
    private Player player;
    private ArrayList<Platform> platforms;
    private ArrayList<Collectible> collectibles;
    private ArrayList<Enemy> enemies;

    public Logic(int level) {
        this.level = level;
        this.player = new Player();
        this.platforms = new ArrayList<>();
        this.collectibles = new ArrayList<>();
        this.enemies = new ArrayList<>();
    }

    public void setUp() {
        this.player.applyGravity();
        //getInput
        this.player.update();
        this.collisions();
    }

    public void run() {
        this.player.applyGravity();
        //getInput
        this.player.update();
        this.collisions();
    }

    public void collisions() {
        Rectangle playerRect = this.player.getBounds();
        for (Platform platform : this.platforms) {
            Rectangle platformRect = platform.getBounds();
            if (playerRect.intersects(platformRect)) {
                if (this.player.vx > 0) {
                    this.player.x = platform.x - this.player.width;
                } else if (player.vx < 0) {
                    this.player.x = platform.x + this.player.width;
                }
                this.player.vx = 0;
                if (this.player.vy > 0) {
                    this.player.y = platform.y - this.player.height;
                    this.player.vy = 0;
                    this.player.onGround = true;
                } else if (this.player.vy < 0) {
                    this.player.y = platform.y + this.player.height;
                    this.player.vy = 0;
                }
            }
        }
        for (Enemy enemy : this.enemies) {
            Rectangle enemyRect = enemy.getBounds();
            if (playerRect.intersects(enemyRect)) {

            }
        }
        for (Collectible collectible : this.collectibles) {
            Rectangle collectibleRect = collectible.getBounds();
            if (playerRect.intersects(collectibleRect)) {

            }
        }

    }

    public void placeEnemy() {
        Vine v = new Vine();
        Enemy enemy = new Enemy(v, this.level);
        this.enemies.add(enemy);
    }

    public void placeCollectible() {
        Collectible collectible = new Collectible();
        this.collectibles.add(collectible);
    }
}
