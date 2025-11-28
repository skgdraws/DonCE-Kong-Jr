package game;

/**
 * Representa un enemigo azul que implementa gravedad en su patrullaje.
 * Se mueve hacia abajo con aceleración por gravedad dentro de la vid.
 */
public class BlueEnemy extends Enemy {
    /**
     * Implementa el patrullaje del enemigo azul con gravedad.
     * Acelera hacia abajo hasta una velocidad máxima de caída.
     */
    @Override
    public void patrol() {
        if (this.y + this.height > this.vine.y + this.vine.height) {
            Double gravity = 0.5;
            this.vy += gravity;
            Double maxFallSpeed = 12.0;
            if (this.vy > maxFallSpeed) {
                this.vy = maxFallSpeed;
            }
        }
    }
}
