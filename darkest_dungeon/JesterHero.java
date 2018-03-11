import java.util.Properties;

public class JesterHero extends  Hero {
    JesterHero(Properties data) {

        super(data);
        System.out.println("tuta");
        battleAbilities.add(1,new JesterDirkStabAbility(this));
        battleAbilities.add(2,new JesterHarvestAbility(this));
    }
    JesterHero() {
        super();
        battleAbilities.add(1,new JesterDirkStabAbility(this));
        battleAbilities.add(2,new JesterHarvestAbility(this));
        maxHP = 19;
        stunResist = 20;
        bleedResist = 40;
        moveResist = 20;
        debuffResist = 40;
        blightResist = 40;
        armor = 0;
        speed = 7;
        dodge = 15;
        accuracy = 100;
        minDamage = 4;
        maxDamage = 7;
        critChance = 7;
        size = 1;
    }

    @Override
    public void moveBack(BattleContext field) {
        field.changeUnitPosition(this,3,MoveDirection.BACK);
    }

    @Override
    public void moveForward(BattleContext field) {
        field.changeUnitPosition(this,3,MoveDirection.FORWARD);
    }

    @Override
    protected void deathWithOutCorpse() {
        System.out.println("Jester dead!");
    }

    @Override
    protected void deathWithCorpse()  {
        System.out.println("Jester dead!");
    }



}
