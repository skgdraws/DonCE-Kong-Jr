package game;

import java.awt.Rectangle;

/**
 * Clase abstracta que representa una entidad en el juego.
 * Define propiedades comunes como posición, velocidad y dimensiones.
 */
public abstract class Entity {
    protected Double x; // Posición X
    protected Double y; // Posición Y
    protected Double vx; // Velocidad en X
    protected Double vy; // Velocidad en Y
    protected Integer width; // Ancho de la entidad
    protected Integer height; // Alto de la entidad

    /**
     * Actualiza la posición de la entidad según su velocidad.
     */
    public void update() {
        this.x += this.vx;
        this.y += this.vy;
    };

    /**
     * Obtiene los límites de la entidad como un rectángulo.
     * @return Rectangle que representa los límites de la entidad
     */
    Rectangle getBounds() {
        return new Rectangle(x.intValue(), y.intValue(), width, height);
    }

    /**
     * Obtiene la posición X de la entidad.
     * @return posición X
     */
    public Double getX() {
        return this.x;
    }

    /**
     * Obtiene la posición Y de la entidad.
     * @return posición Y
     */
    public Double getY() {
        return this.y;
    }

    /**
     * Obtiene el ancho de la entidad.
     * @return ancho en píxeles
     */
    public Integer getWidth() {
        return this.width;
    }

    /**
     * Obtiene el alto de la entidad.
     * @return alto en píxeles
     */
    public Integer getHeight() {
        return this.height;
    }

    /**
     * Obtiene la velocidad vertical de la entidad.
     * @return velocidad en Y
     */
    public Double getVY() {
        return this.vy;
    }
}
