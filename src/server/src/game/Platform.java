package game;

/**
 * Representa una plataforma en el juego.
 * Las plataformas son estructuras estáticas sobre las que el jugador puede caminar.
 */
public class Platform extends Entity {
    /**
     * Constructor de una plataforma.
     * @param x posición X
     * @param y posición Y
     * @param width ancho de la plataforma
     * @param height alto de la plataforma
     */
    public Platform(Double x, Double y, Integer width, Integer height) {
        this.x = x;
        this.y = y;
        this.width = width;
        this.height = height;
        this.vx = 0.0;
        this.vy = 0.0;
    }
}
