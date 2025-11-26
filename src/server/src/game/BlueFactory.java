package game;

public class BlueFactory extends EnemyFactory{
    @Override
    public Enemy createEnemy() {
        return new BlueEnemy();
    }
}
