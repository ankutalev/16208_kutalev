public class MoveAbility extends Ability {
    MoveAbility(int maxBack,int maxForward) {
        this.maxBack = maxBack;
        this.maxForward = maxForward;
    }

    @Override
    boolean isLegal(BattleContext field) {
       int currentPos = field.getUnitPosition(this.user);
        return false;
    }

    @Override
    void upgrade() {

    }

    @Override
    public void choseTargets(BattleContext field) {

    }

    @Override
    void using(BattleContext field) {

    }
    private int maxForward;
    private int maxBack;
}
