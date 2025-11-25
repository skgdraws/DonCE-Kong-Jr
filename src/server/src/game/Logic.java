package game;

import java.awt.*;
import java.util.ArrayList;
import java.util.Objects;

public class Logic {
    private int level;
    private Player player;
    private ArrayList<Platform> platforms;
    private ArrayList<Vine> vines;
    private ArrayList<Collectible> collectibles;
    private ArrayList<Enemy> enemies;

    public Logic(int level) {
        this.level = level;
        this.player = new Player();
        this.platforms = new ArrayList<>();
        this.vines = new ArrayList<>();
        this.collectibles = new ArrayList<>();
        this.enemies = new ArrayList<>();
    }

    public void setUp() {
        this.platforms.add(new Platform(0, 0, 0, 0));
        this.platforms.add(new Platform(0, 0, 0, 0));
        this.platforms.add(new Platform(0, 0, 0, 0));
        this.platforms.add(new Platform(0, 0, 0, 0));
        this.platforms.add(new Platform(0, 0, 0, 0));
        this.platforms.add(new Platform(0, 0, 0, 0));
        this.platforms.add(new Platform(0, 0, 0, 0));
        this.platforms.add(new Platform(0, 0, 0, 0));
        this.platforms.add(new Platform(0, 0, 0, 0));
        this.platforms.add(new Platform(0, 0, 0, 0));
        this.platforms.add(new Platform(0, 0, 0, 0));
        this.platforms.add(new Platform(0, 0, 0, 0));

        this.vines.add(new Vine(0, 0, 0, 0));
        this.vines.add(new Vine(0, 0, 0, 0));
        this.vines.add(new Vine(0, 0, 0, 0));
        this.vines.add(new Vine(0, 0, 0, 0));
        this.vines.add(new Vine(0, 0, 0, 0));
        this.vines.add(new Vine(0, 0, 0, 0));
        this.vines.add(new Vine(0, 0, 0, 0));
        this.vines.add(new Vine(0, 0, 0, 0));
        this.vines.add(new Vine(0, 0, 0, 0));
        this.vines.add(new Vine(0, 0, 0, 0));
        this.vines.add(new Vine(0, 0, 0, 0));
        this.vines.add(new Vine(0, 0, 0, 0));
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
        for (Vine vine : this.vines) {
            Rectangle vineRect = vine.getBounds();
            this.player.climbing = playerRect.intersects(vineRect);
        }
        for (Enemy enemy : this.enemies) {
            Rectangle enemyRect = enemy.getBounds();
            if (playerRect.intersects(enemyRect)) {
                this.player.lives -= 1;
                if (this.player.lives < 0) {
                    return;
                }
            }
        }
        for (Collectible collectible : this.collectibles) {
            Rectangle collectibleRect = collectible.getBounds();
            if (playerRect.intersects(collectibleRect)) {
                this.player.score += collectible.value;
            }
        }
    }

    public void placeEnemy(String kind, int vineIndex) {
        Vine vine = this.vines.get(vineIndex);
        Enemy enemy = switch (kind) {
            case "blue" -> new BlueEnemy(vine, this.level);
            case "red" -> new RedEnemy(vine, this.level);
            default -> null;
        };
        if (enemy != null) {
            this.enemies.add(enemy);
        }
    }

    public void placeCollectible(String kind, int x, int y) {
        Collectible collectible = switch (kind) {
            case "banana" -> new Banana(x, y);
            case "orange" -> new Orange(x, y);
            case "strawberry" -> new Strawberry(x, y);
            default -> null;
        };
        if (collectible != null) {
            this.collectibles.add(collectible);
        }
    }
}
