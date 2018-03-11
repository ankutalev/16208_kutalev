public class SkipTurn extends Ability {
    SkipTurn(Unit user) {
        this.user = user;
        setName("Skip turn");
    }
    @Override
    boolean isLegal(BattleContext field) {
        return true;
    }

    @Override
    void upgrade() { }

    @Override
    public void choseTargets(BattleContext field) { }

    @Override
    void using(BattleContext field) {
        System.out.println(user.getClass().getSimpleName()+"skipped turn!");
    }
}
