package game;

import java.lang.Math;

/**
 * Clase que representa al jugador en el juego.
 * Hereda de Entity e implementa lógica de movimiento, saltos y escalada.
 */
public class Player extends Entity {
    protected Integer lives; // Vidas del jugador
    protected Integer score; // Puntuación del jugador
    protected Boolean onGround; // Indica si está en el suelo
    protected Boolean climbing; // Indica si está escalando una liana
    protected Boolean jumping; // Indica si está en medio de un salto
    protected String currentDirection; //Indica la dirección actual del jugador
    protected String lastHorizontalDirection; // Última dirección horizontal para el sprite

    /**
     * Constructor del jugador.
     * Inicializa con 3 vidas, puntuación 0 y dimensiones específicas.
     */
    public Player() {
        this.lives = 3;
        this.score = 0;
        this.onGround = false;
        this.climbing = false;
        this.jumping = false;
        this.currentDirection = "none";
        this.lastHorizontalDirection = "left";
        this.width = 16;
        this.height = 16;
        this.vx = 0.0;
        this.vy = 0.0;
    }

    /**
     * Obtiene las vidas del jugador.
     * @return número de vidas
     */
    public int getLives() {
        return this.lives;
    }

    /**
     * Obtiene la puntuación del jugador.
     * @return puntuación actual
     */
    public int getScore() {
        return this.score;
    }

    public String getState() {
        if (this.climbing) {
            return "climbing";
        } else if (this.jumping || !this.onGround) {
            return "jumping";
        } else if (Math.abs(this.vx) > 0.5) {
            return "walking";
        } else {
            return "idle";
        }
    }

    /**
     * Obtiene la dirección hacia la que mira el jugador.
     * @return "right" si mira a la derecha, "left" si mira a la izquierda
     */
    public String getFacingDirection() {
        return this.lastHorizontalDirection;
    }

    /**
     * Aplica la gravedad al jugador cuando no está en el suelo ni escalando.
     * Incrementa la velocidad Y hasta una velocidad máxima de caída.
     */
    public void applyGravity() {
        if (!this.onGround && !this.climbing) {
            Double gravity = 0.5;
            this.vy += gravity;
            Double maxFallSpeed = 12.0;
            if (this.vy > maxFallSpeed) {
                this.vy = maxFallSpeed;
            }
        }
    }

    /**
     * Realiza un salto, estableciendo la velocidad Y negativa.
     * El jugador deja de estar en el suelo.
     */
    public void jump() {
        if (this.onGround  || this.climbing) {
            this.vy = -5.0;
            this.onGround = false;
            this.climbing = false;
            this.jumping = true;
        }
    }

    /**
     * Reduce gradualmente la velocidad horizontal del jugador.
     * Simula fricción para frenar al jugador.
     */
    public void stop() {
        // Immediately stop horizontal movement
        this.vx = 0.0;
        
        // If climbing, also stop vertical movement
        if (this.climbing) {
            this.vy = 0.0;
        }
    }

    /**
     * Mueve al jugador en una dirección especificada.
     * Soporta movimiento izquierda, derecha, arriba (escalada/salto) y abajo (descenso).
     * @param direction dirección del movimiento: "left", "right", "up", "down"
     */
    public void move(String direction) {
        Double moveSpeed = 3.0;  // Constant horizontal speed
        Double climbSpeed = 2.0; // Constant climbing speed

        this.currentDirection = direction;
        
        // Guardar la última dirección horizontal para el sprite
        if (direction.equals("left") || direction.equals("right")) {
            this.lastHorizontalDirection = direction;
        }
        
        switch (direction) {
            case "up":
                if (this.climbing) {
                    this.vy = -climbSpeed;  // Set constant climbing speed
                }
                break;
            case "down":
                if (this.climbing) {
                    this.vy = climbSpeed;  // Set constant climbing speed
                }
                break;
            case "left":
                this.vx = -moveSpeed;  // Set constant speed left
                break;
            case "right":
                this.vx = moveSpeed;   // Set constant speed right
                break;
            case "jump":
                this.jump();
                break;
            default:
                this.stop();
                break;
        }
    }
}
