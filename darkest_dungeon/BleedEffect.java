public class BleedEffect extends TickedEffects {
    BleedEffect(int damage,int ticks) {
        this.ticks = ticks;
        this.damage = damage;
    }
    @Override
    public void makeEffect(Unit unit,BattleContext field) {
            unit.takeDamage((short)damage, DamageType.PURE,field);
            System.out.println(unit.getClass().getSimpleName() + " bleeded for " +damage);
    }
    private int damage;
}
