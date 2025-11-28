package game;

import java.awt.*;
import java.util.ArrayList;
import java.util.Iterator;

/**
 * Clase que gestiona la lógica del juego Donkey Kong Jr.
 * Controla la física, colisiones, entidades y el estado general del juego.
 * Implementa GameSubject para notificar a espectadores (patrón Observer).
 */
public class Logic implements GameSubject {
    private Integer level; // Nivel actual del juego
    private Player player; // Instancia del jugador
    private ArrayList<Platform> platforms; // Lista de plataformas
    private ArrayList<Vine> vines; // Lista de liana
    private ArrayList<Collectible> collectibles; // Lista de frutas coleccionables
    private ArrayList<Enemy> enemies; // Lista de enemigos
    private Rectangle Boss; // Rectángulo del jefe (Mario)
    private Rectangle Goal; // Rectángulo del objetivo (plataforma final)
    private ArrayList<GameObserver> observers; // Lista de observadores (espectadores)

    /**
     * Constructor de Logic.
     * @param level nivel inicial del juego
     */
    public Logic(int level) {
        this.level = level;
        this.player = new Player();
        this.platforms = new ArrayList<>();
        this.vines = new ArrayList<>();
        this.collectibles = new ArrayList<>();
        this.enemies = new ArrayList<>();
        this.observers = new ArrayList<>();
        this.setMap();
        this.setPlayer();
    }

    /**
     * Configura el mapa del juego inicializando plataformas, lianas, jefe y objetivo.
     */
    public void setMap() {
        this.platforms.add(new Platform(56.0, 40., 24, 8));
        this.platforms.add(new Platform(0.0, 72.0, 136, 8));
        this.platforms.add(new Platform(128.0, 80.0, 64, 8));
        this.platforms.add(new Platform(32.0, 120.0, 32, 8));
        this.platforms.add(new Platform(176.0, 144.0, 48, 8));
        this.platforms.add(new Platform(32.0, 168.0, 48, 8));
        this.platforms.add(new Platform(0.0, 240.0, 56, 8));
        this.platforms.add(new Platform(80.0, 224.0, 32, 8));
        this.platforms.add(new Platform(120.0, 232.0, 24, 8));
        this.platforms.add(new Platform(152.0, 224.0, 32, 8));
        this.platforms.add(new Platform(192.0, 216.0, 32, 8));

        this.vines.add(new Vine(1.0, 80.0, 6, 144));
        this.vines.add(new Vine(25.0, 80.0, 6, 136));
        this.vines.add(new Vine(49.0, 128.0, 6, 40));
        this.vines.add(new Vine(49.0, 176.0, 6, 48));
        this.vines.add(new Vine(89.0, 80.0, 6, 120));
        this.vines.add(new Vine(121.0, 80.0, 6, 72));
        this.vines.add(new Vine(145.0, 88.0, 6, 112));
        this.vines.add(new Vine(169.0, 88.0, 6, 96));
        this.vines.add(new Vine(193.0, 152.0, 6, 48));
        this.vines.add(new Vine(217.0, 152.0, 6, 48));
        this.vines.add(new Vine(193.0, 0.0, 6, 144));
        this.vines.add(new Vine(217.0, 0.0, 6, 144));
        this.vines.add(new Vine(137.0, 0.0, 6, 48));
        this.vines.add(new Vine(89.0, 0.0, 6, 48));

        this.Boss = new Rectangle(56, 56, 16, 16);
        this.Goal = new Rectangle(0, 39, 80, 1);
    }

    /**
     * Reinicia la posición del jugador a la posición inicial.
     */
    public void setPlayer() {
        this.player.x = 6.0;
        this.player.y = 224.0;
        this.player.vx = 0.0;
        this.player.vy = 0.0;
        this.player.onGround = false;
        this.player.climbing = false;
    }

    /**
     * Ejecuta el bucle principal del juego.
     * Aplica gravedad, actualiza el jugador y verifica colisiones mientras el jugador tenga vidas.
     */
    public void run() {
        while (this.player.lives >= 0) {
            this.player.applyGravity();
            //getInput
            this.player.update();
            this.collisions();
        }
    }

    /**
     * Verifica y maneja todas las colisiones en el juego.
     * Incluye colisiones con plataformas, lianas, enemigos, frutas y objetivos.
     */
    public void collisions() {
        Rectangle playerRect = this.player.getBounds();
        
        // Reset onGround flag - will be set to true if player is on a platform
        this.player.onGround = false;
        
        // Save previous climbing state before resetting
        Boolean wasClimbing = this.player.climbing;
        
        // Reset climbing state - will be set to true if player is on a vine
        this.player.climbing = false;
        
        // Check vine collisions to set climbing state
        // Only grab vine if player is pressing up/down AND is not jumping (vy < 0 means going up from jump)
        Boolean isJumping = this.player.vy < 0 && !wasClimbing;
        for (Vine vine : this.vines) {
            Rectangle vineRect = vine.getBounds();
            Boolean wantsToClimb = this.player.currentDirection.equals("up") || this.player.currentDirection.equals("down");
            
            if (playerRect.intersects(vineRect) && wantsToClimb && !isJumping) {
                this.player.climbing = true;
                this.player.x = vine.x + vine.width / 2 - this.player.width / 2;
                
                // If player just grabbed the vine (wasn't climbing before), stop vertical momentum
                if (!wasClimbing) {
                    this.player.vy = 0.0;
                }
                break;
            }
        }
        
        // Platform collisions
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
                
                // Resolve collision based on the direction with smallest overlap
                if (minOverlap == overlapTop && this.player.vy >= 0) {
                    // Colliding from top (player landing on platform)
                    this.player.y = platform.y - this.player.height;
                    this.player.vy = 0.0;
                    this.player.onGround = true;
                } else if (minOverlap == overlapBottom && this.player.vy <= 0) {
                    // Colliding from bottom (player hitting ceiling)
                    this.player.y = platform.y + platform.height;
                    this.player.vy = 0.0;
                } else if (minOverlap == overlapLeft && this.player.vx > 0) {
                    // Colliding from left side
                    this.player.x = platform.x - this.player.width;
                    this.player.vx = 0.0;
                } else if (minOverlap == overlapRight && this.player.vx < 0) {
                    // Colliding from right side
                    this.player.x = platform.x + platform.width;
                    this.player.vx = 0.0;
                }
            }
        }
        
        // Additional ground check: if player is very close to top of platform and moving down slowly
        if (!this.player.onGround && !this.player.climbing && this.player.vy >= 0) {
            for (Platform platform : this.platforms) {
                double playerBottom = this.player.y + this.player.height;
                double playerLeft = this.player.x;
                double playerRight = this.player.x + this.player.width;
                double platformTop = platform.y;
                double platformLeft = platform.x;
                double platformRight = platform.x + platform.width;
                
                // Check if player is horizontally aligned with platform
                boolean horizontalOverlap = playerRight > platformLeft && playerLeft < platformRight;
                
                // Check if player is very close to top of platform (within 2 pixels)
                double distanceToTop = playerBottom - platformTop;
                
                if (horizontalOverlap && distanceToTop >= 0 && distanceToTop <= 2) {
                    this.player.y = platformTop - this.player.height;
                    this.player.vy = 0.0;
                    this.player.onGround = true;
                    break;
                }
            }
        }
        
        // Verificar colisión con enemigos - usar flag para evitar ConcurrentModificationException
        boolean hitEnemy = false;
        for (Enemy enemy : this.enemies) {
            Rectangle enemyRect = enemy.getBounds();
            if (playerRect.intersects(enemyRect)) {
                hitEnemy = true;
                System.out.println("Player hit enemy at (" + enemy.getX() + ", " + enemy.getY() + ")");
                break;  // Salir del loop antes de modificar la lista
            }
        }
        if (hitEnemy) {
            System.out.println("Clearing enemies and resetting player. Lives remaining: " + (this.player.lives - 1));
            this.player.lives -= 1;
            this.enemies.clear();
            this.collectibles.clear();
            this.setPlayer();
        }
        
        // Verificar colisión con Boss o caer fuera de pantalla
        if (playerRect.intersects(Boss) || this.player.y + this.player.height > 256) {
            this.player.lives -= 1;
            this.enemies.clear();
            this.collectibles.clear();
            this.setPlayer();
        }

        for (Integer i = this.collectibles.size() - 1; i >= 0; i--) {
            Collectible collectible = this.collectibles.get(i);
            Rectangle collectibleRect = collectible.getBounds();
            if (playerRect.intersects(collectibleRect)) {
                this.player.score += collectible.value;
                this.collectibles.remove(i.intValue());
            }
        }
        if (playerRect.intersects(Goal)) {
            if (this.player.lives < 6) {
                this.player.lives += 1;
            }
            this.level += 1;
            this.enemies.clear();
            this.collectibles.clear();
            this.setPlayer();
        }
    }

    /**
     * Coloca un enemigo en una liana específica del mapa.
     * @param factory fábrica para crear el tipo de enemigo
     * @param vineIndex índice de la liana donde se colocará el enemigo
     */
    public void placeEnemy(EnemyFactory factory, int vineIndex) {
        Enemy enemy = factory.createEnemy();
        enemy.place(this.vines.get(vineIndex));
        enemy.setLevel(this.level);
        this.enemies.add(enemy);
    }

    /**
     * Coloca un objeto coleccionable en una posición específica del mapa.
     * @param factory fábrica para crear el tipo de coleccionable
     * @param vineIndex liana en la que se va a colocar la fruta
     * @param y posición Y
     * @param value ountaje a asignar a alla afrutap
     */
    public void placeCollectible(CollectibleFactory factory, int vineIndex, double y, int value) {
        Vine vine = this.vines.get(vineIndex);
        double target_y = y;
        Collectible collectible = factory.createCollectible();
        if (target_y > vine.height) {
            target_y = vine.height;
        }
        collectible.place(vine.x, vine.y + target_y, value);
        this.collectibles.add(collectible);
    }

    /**
     * Elimina un coleccionable de la lista que coincida con los parámetros especificados.
     * Si no se encuentra ninguno, no hace nada.
     * @param vineIdx índice de la liana donde se encuentra el coleccionable
     * @param y posición Y del coleccionable a eliminar
     */
    public void deleteCollectible(int vineIdx, double y) {
        Vine vine = this.vines.get(vineIdx);
        double target_y = vine.y + y;

        for (Integer i = this.collectibles.size() - 1; i >= 0; i--) {
            Collectible collectible = this.collectibles.get(i);
            if (collectible.x == vine.x && collectible.y == target_y) {
                this.collectibles.remove(i.intValue());
                return;
            }
        }
    }

    /**
     * Obtiene la instancia del jugador.
     * @return el jugador
     */
    public Player getPlayer() {
        return this.player;
    }

    /**
     * Obtiene la lista de enemigos activos en el juego.
     * @return lista de enemigos
     */
    public ArrayList<Enemy> getEnemies() {
        return this.enemies;
    }

    /**
     * Obtiene la lista de coleccionables activos en el juego.
     * @return lista de coleccionables
     */
    public ArrayList<Collectible> getCollectibles() {
        return this.collectibles;
    }

    // ==================== Implementación del patrón Observer ====================

    /**
     * Agrega un observador (espectador) al juego.
     * @param observer observador a agregar
     */
    @Override
    public void addObserver(GameObserver observer) {
        if (!this.observers.contains(observer)) {
            this.observers.add(observer);
            System.out.println("Observer added. Total observers: " + this.observers.size());
        }
    }

    /**
     * Remueve un observador del juego.
     * @param observer observador a remover
     */
    @Override
    public void removeObserver(GameObserver observer) {
        this.observers.remove(observer);
        System.out.println("Observer removed. Total observers: " + this.observers.size());
    }

    /**
     * Notifica a todos los observadores del estado actual del juego.
     * Remueve observadores inactivos automáticamente.
     * @param gameState estado del juego serializado
     */
    @Override
    public void notifyObservers(String gameState) {
        // Usar iterator para poder remover durante iteración
        Iterator<GameObserver> iterator = this.observers.iterator();
        while (iterator.hasNext()) {
            GameObserver observer = iterator.next();
            if (observer.isActive()) {
                observer.onGameStateUpdate(gameState);
            } else {
                iterator.remove();
                System.out.println("Inactive observer removed. Total observers: " + this.observers.size());
            }
        }
    }

    /**
     * Obtiene el número de observadores activos.
     * @return cantidad de observadores
     */
    public Integer getObserverCount() {
        return this.observers.size();
    }
}
