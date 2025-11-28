package game;

/**
 * Clase abstracta que define la interfaz para crear enemigos.
 * Implementa el patrón Factory para la creación de diferentes tipos de enemigos.
 */
public abstract class EnemyFactory {
    /**
     * Método abstracto para crear un enemigo.
     * @return una instancia de un enemigo específico
     */
    public abstract Enemy createEnemy();
}
