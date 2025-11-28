package game;

import java.awt.*;
import java.util.ArrayList;

public class Logic {
    private int level;
    private Player player;
    private ArrayList<Platform> platforms;
    private ArrayList<Vine> vines;
    private ArrayList<Collectible> collectibles;
    private ArrayList<Enemy> enemies;
    private Rectangle Boss;
    private Rectangle Goal;

    public Logic(int level) {
        this.level = level;
        this.player = new Player();
        this.platforms = new ArrayList<>();
        this.vines = new ArrayList<>();
        this.collectibles = new ArrayList<>();
        this.enemies = new ArrayList<>();
        this.setMap();
    }

    public void setMap() {
        this.platforms.add(new Platform(56, 40, 24, 8));
        this.platforms.add(new Platform(0, 72, 136, 8));
        this.platforms.add(new Platform(128, 80, 64, 8));
        this.platforms.add(new Platform(32, 120, 32, 8));
        this.platforms.add(new Platform(176, 144, 48, 8));
        this.platforms.add(new Platform(32, 168, 48, 8));
        this.platforms.add(new Platform(0, 240, 56, 8));
        this.platforms.add(new Platform(80, 224, 32, 8));
        this.platforms.add(new Platform(120, 132, 24, 8));
        this.platforms.add(new Platform(152, 224, 32, 8));
        this.platforms.add(new Platform(192, 216, 32, 8));

        this.vines.add(new Vine(1, 80, 6, 144));
        this.vines.add(new Vine(25, 80, 6, 136));
        this.vines.add(new Vine(49, 128, 6, 40));
        this.vines.add(new Vine(49, 176, 6, 48));
        this.vines.add(new Vine(89, 80, 6, 120));
        this.vines.add(new Vine(121, 80, 6, 72));
        this.vines.add(new Vine(145, 88, 6, 112));
        this.vines.add(new Vine(169, 88, 6, 96));
        this.vines.add(new Vine(193, 152, 6, 48));
        this.vines.add(new Vine(217, 152, 6, 48));
        this.vines.add(new Vine(193, 0, 6, 144));
        this.vines.add(new Vine(217, 0, 6, 144));
        this.vines.add(new Vine(137, 0, 6, 48));
        this.vines.add(new Vine(89, 0, 6, 48));

        this.Boss = new Rectangle(56, 56, 16, 16);
        this.Goal = new Rectangle(0, 40, 48, 32);
    }

    public void setPlayer() {
        this.player.x = 6;
        this.player.y = 224;
        this.player.vx = 0;
        this.player.vy = 0;
        this.player.onGround = false;
        this.player.climbing = false;
    }

    public void run() {
        while (this.player.lives >= 0) {
            this.player.applyGravity();
            //getInput
            this.player.update();
            this.collisions();
        }
    }

    public void collisions() {
        Rectangle playerRect = this.player.getBounds();
        
        // Reset onGround flag - will be set to true if player is on a platform
        this.player.onGround = false;
        
        for (Platform platform : this.platforms) {
            Rectangle platformRect = platform.getBounds();
            if (playerRect.intersects(platformRect)) {
                // Calculate overlap amounts
                double overlapLeft = (this.player.x + this.player.width) - platform.x;
                double overlapRight = (platform.x + platform.width) - this.player.x;
                double overlapTop = (this.player.y + this.player.height) - platform.y;
                double overlapBottom = (platform.y + platform.height) - this.player.y;
                
                // Find the smallest overlap to determine collision direction
                double minOverlap = Math.min(Math.min(overlapLeft, overlapRight), 
                                            Math.min(overlapTop, overlapBottom));
                
                // Only resolve collision if overlap is significant (prevents jittering)
                if (minOverlap < 0.1) continue;
                
                // Resolve collision based on the direction with smallest overlap
                if (minOverlap == overlapTop && this.player.vy >= 0) {
                    // Colliding from top (player landing on platform)
                    this.player.y = platform.y - this.player.height;
                    this.player.vy = 0;
                    this.player.onGround = true;
                } else if (minOverlap == overlapBottom && this.player.vy < 0) {
                    // Colliding from bottom (player hitting ceiling)
                    this.player.y = platform.y + platform.height;
                    this.player.vy = 0;
                } else if (minOverlap == overlapLeft && this.player.vx > 0) {
                    // Colliding from left side
                    this.player.x = platform.x - this.player.width;
                    this.player.vx = 0;
                } else if (minOverlap == overlapRight && this.player.vx < 0) {
                    // Colliding from right side
                    this.player.x = platform.x + platform.width;
                    this.player.vx = 0;
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
                this.setPlayer();
            }
        }
        if (playerRect.intersects(Boss) || this.player.y + this.player.height > 256) {
            this.player.lives -= 1;
            this.setPlayer();
        }
        for (Collectible collectible : this.collectibles) {
            Rectangle collectibleRect = collectible.getBounds();
            if (playerRect.intersects(collectibleRect)) {
                this.player.score += collectible.value;
            }
        }
        if (playerRect.intersects(Goal)) {
            this.player.lives += 1;
            this.level += 1;
            this.setPlayer();
        }
    }

    public void placeEnemy(EnemyFactory factory, int vineIndex) {
        Enemy enemy = factory.createEnemy();
        enemy.place(this.vines.get(vineIndex));
        enemy.setLevel(this.level);
        this.enemies.add(enemy);
    }

    public void placeCollectible(CollectibleFactory factory, int x, int y) {
        Collectible collectible = factory.createCollectible();
        collectible.place(x, y);
        this.collectibles.add(collectible);
    }

    public Player getPlayer() {
        return this.player;
    }

    public ArrayList<Enemy> getEnemies() {
        return this.enemies;
    }

    public ArrayList<Collectible> getCollectibles() {
        return this.collectibles;
    }
}
