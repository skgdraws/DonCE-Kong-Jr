package game;

/**
 * Representa un enemigo rojo que patrulla hacia arriba y abajo en una vid.
 * Invierte su dirección cuando alcanza los límites de la vid.
 */
public class RedEnemy extends Enemy {
    /**
     * Implementa el patrullaje del enemigo rojo.
     * Se mueve verticalmente dentro de los límites de la vid.
     */
    @Override
    public void patrol() {
        if (this.y + this.height > this.vine.y + this.vine.height) {
            this.vy = -this.vy;
        } else if (this.y < this.vine.y) {
            this.vy = -this.vy;
        }
    }
}
