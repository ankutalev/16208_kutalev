public abstract class TickedEffects implements Effect {
    final public void giveInfluence(Unit unit,BattleContext field) {
        if (ticks>0) {
            makeEffect(unit,field);
            ticks--;
        }
        else
            unit.loseEffect(this);
    }
    abstract public void makeEffect(Unit unit,BattleContext field);
    protected int ticks = 3;
}
