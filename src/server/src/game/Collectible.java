package game;

/**
 * Clase abstracta que representa un objeto coleccionable en el juego.
 * Las frutas son ejemplos de objetos coleccionables.
 */
public class Collectible extends Entity {
    protected Integer value; // Valor de puntos que otorga este coleccionable

    /**
     * Coloca el objeto coleccionable en una posición específica.
     * @param x posición X
     * @param y posición Y
     * @param value puntaje a otorgar
     */
    public void place (Double x, Double y, Integer value) {
        this.x = x;
        this.y = y;
        this.vx = 0.0;
        this.vy = 0.0;
        this.value = value;
    }
}
