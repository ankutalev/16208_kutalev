import java.util.ArrayList;
import java.util.Random;
import java.util.concurrent.ThreadLocalRandom;

public abstract class Unit {
    Unit(String data) {
        //todo: add data parsing for fields;
        currentTickedEffects = new ArrayList<>();
    }
    public abstract void move(BattleContext field);
    public  void battleTurn(BattleContext field) {
        for (Effect eff: currentTickedEffects)
            eff.giveInfluence();
        battleAction(field);
    }
    public abstract void battleAction(BattleContext field);
    public abstract void skipTurn();
    protected abstract void deathWithCorpse();
    protected abstract void deathWithOutCorpse();

    protected short getArmor() {
        return armor;
    }

    protected short getMaxHP() {
        return maxHP;
    }

    protected short getCurrentHP() {
        return currentHP;
    }

    protected boolean isItDeathDoor(short dmg) {
        if (dmg==0) return false;
        this.currentHP -= dmg;
        if (this.currentHP<=0) {
            this.currentHP = 0;
            return true;
        }
        return false;
    }

    public abstract void takeDamage(short dmg, DamageType type);
    private short maxHP=20;
    private short stunResist=100;
    private short bleedResist=100;
    private short moveResist=100;
    private short debuffResist=100;
    private short blightResist=100;
    private short armor=0;
    private short speed=6;
    private short dodge=10;
    private short accuracy=100;
    private short minDamage=9;
    private short maxDamage = 14;
    private short critChance = 15;
    private short currentHP=maxHP;
    private ArrayList<tickedEffects> currentTickedEffects;
}
