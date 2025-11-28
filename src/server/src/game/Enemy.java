package game;

/**
 * Clase abstracta que representa un enemigo en el juego.
 * Los enemigos se posicionan en lianas y patrullan en ellas.
 */
public abstract class Enemy extends Entity {
    protected Vine vine; // Referencia a la liana en la que patrulla el enemigo

    /**
     * Coloca el enemigo en una liana específica.
     * @param vine la liana donde se posicionará el enemigo
     */
    public void place(Vine vine) {
        this.vine = vine;
        this.y = vine.y;
        this.width = 16;
        this.height = 16;
        this.x = vine.x + vine.width / 2 - this.width / 2;
    }

    /**
     * Establece la velocidad del enemigo según el nivel del juego.
     * A mayor nivel, mayor velocidad de patrulla.
     * @param level nivel del juego
     */
    public void setLevel(Integer level) {
        this.vx = 0.0;
        this.vy = 0.5 + 0.5 * level;
    }

    /**
     * Define el comportamiento de patrulla del enemigo.
     * Cada tipo de enemigo implementa su propio patrullaje.
     */
    public abstract void patrol();
}
