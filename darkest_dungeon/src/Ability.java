public abstract class Ability {
    abstract void  using (BattleContext field);
    abstract boolean isLegal(BattleContext field);

    public String getName() {
        return name;
    }
    abstract void upgrade();
    protected byte level = 0;
    protected boolean isPurchased = false;
    protected boolean isActive = false;
    protected String name;
}
