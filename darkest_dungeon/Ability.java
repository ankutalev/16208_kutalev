import java.util.ArrayList;

public abstract class Ability {
    abstract public void choseTargets(BattleContext field);
    abstract void  using (BattleContext field);
    abstract boolean isLegal(BattleContext field);

    public String getName() {
        return name;
    }
    abstract void upgrade();
    protected byte level = 0;
    protected boolean isPurchased = false;
    protected boolean isActive = false;
    protected  void setName(String name) {
        this.name = name;
    }


    private String name;
    protected ArrayList<Unit> targets = new ArrayList<>();
    protected Unit user;
    //protected
}
