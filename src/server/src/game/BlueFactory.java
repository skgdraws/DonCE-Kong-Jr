package game;

/**
 * Fábrica para crear enemigos azules.
 * Implementa el patrón Factory para la creación de BlueEnemy.
 */
public class BlueFactory extends EnemyFactory {
    /**
     * Crea y retorna una instancia de un enemigo azul.
     * @return un nuevo BlueEnemy
     */
    @Override
    public Enemy createEnemy() {
        return new BlueEnemy();
    }
}
