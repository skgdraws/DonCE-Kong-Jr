package game;

public class RedFactory extends EnemyFactory{
    @Override
    public Enemy createEnemy() {
        return new RedEnemy();
    }
}
