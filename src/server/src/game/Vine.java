package game;
/**
 * Representa una liana en el juego.
 * Las lianas son estructuras verticales que el jugador puede escalar.
 */
public class Vine extends Entity {
    /**
     * Constructor de una liana.
     * @param x posición X
     * @param y posición Y
     * @param width ancho de la liana
     * @param height alto de la liana
     */
    public Vine(Double x, Double y, Integer width, Integer height) {
        this.x = x;
        this.y = y;
        this.width = width;
        this.height = height;
        this.vx = 0.0;
        this.vy = 0.0;
    }
}
