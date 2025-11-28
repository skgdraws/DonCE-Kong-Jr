package game;

/**
 * Fábrica para crear enemigos rojos.
 * Implementa el patrón Factory para la creación de RedEnemy.
 */
public class RedFactory extends EnemyFactory{
    /**
     * Crea y retorna una instancia de un enemigo rojo.
     * @return un nuevo RedEnemy
     */
    @Override
    public Enemy createEnemy() {
        return new RedEnemy();
    }
}
