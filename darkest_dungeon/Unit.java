import java.lang.reflect.Field;
import java.util.ArrayList;
import java.util.Properties;
import java.util.concurrent.ThreadLocalRandom;

public abstract class Unit  implements Comparable{
    Unit(Properties data) {
        //todo: add data parsing for fields;
       // data.list(System.out);
        Field[] fields = this.getClass().getDeclaredFields();
        System.out.println(fields.length);
        for (Field f: fields) {
            System.out.println(f.getName());
            if (data.containsKey(f.getName())) {
                f.setAccessible(true);
                try {
                    System.out.println( f.getName()+ "  "+ data.get(f.getName()));
                    f.set(this, data.get(f.getName()));
                }
                catch (Exception exc) {
                    System.out.println("SWYASHENNAYA ROWA OSKVERNENA!");
                }
            }
        }
        currentTickedEffects = new ArrayList<>();
    }


    Unit () {
        currentTickedEffects = new ArrayList<>(); //todo: normal constructors
        battleAbilities = new ArrayList<>();
        battleAbilities.add(0,new SkipTurn(this));
    }

    public void takeTickedEffect(TickedEffects eff) {
        currentTickedEffects.add(eff);
    }

    public abstract void moveBack(BattleContext field); // todo: move functions

    public void info() {
        System.out.println(this.getClass().getSimpleName() +"  Curent HP: "+ currentHP);
    }

    public  void moveForward(BattleContext field) {
        int index = field.getUnitPosition(this);


    }

    public  void battleTurn(BattleContext field) {
        for (Effect eff: currentTickedEffects)
            eff.giveInfluence(this,field);
        battleAction(field);
    }
    public  void battleAction(BattleContext field) {
            battleAbilities.get(0).using(field); //todo: это заглушка каждый юнит должен будет переопределить батл экшон
    }
    protected  void deathWithCorpse() {
        System.out.println(this.getClass().getSimpleName() + " dead and now it is his corpse!");
    }
    protected abstract void deathWithOutCorpse();

    boolean isHero() {
        return (this.getClass().getSuperclass().getSimpleName().equals("Hero"));
    }

    protected short getArmor() {
        return armor;
    }

    protected short getMaxHP() {
        return maxHP;
    }

    protected short getCurrentHP() {
        return currentHP;
    }

    protected  short getSpeed() {
        return speed;
    }

    protected boolean isItDeathDoor(short dmg) {
        if (dmg==0) return false;
        this.currentHP -= dmg;
        if (this.currentHP<=0) {
            //this.currentHP = 0;
            return true;
        }
        return false;
    }

    public void loseEffect( TickedEffects eff) {
        currentTickedEffects.remove(eff);
    }

    boolean dealDamage(Unit target,double penalty, BattleContext field) {
        short dmg =(short) (ThreadLocalRandom.current().nextInt(minDamage,maxDamage+1)*(1.0 -penalty));
        int critCheck = ThreadLocalRandom.current().nextInt(0,101);
        if (critCheck <= critChance) {
            System.out.println(this.getClass().getSimpleName() + " CRITICAL STRIKE!");
           return target.takeDamage((short)(maxDamage + maxDamage/2),DamageType.CRITICAL,field);
        }
        else
           return target.takeDamage(dmg,DamageType.PHYSICAL,field);
    }

    public  boolean takeDamage(short dmg, DamageType type,BattleContext field) {
        short dmgDealt=dmg;
        if (type !=DamageType.PURE) {
            dmgDealt = (armor==0) ? dmgDealt : (short)(armor *dmg / 100);
        }
        boolean deathCheck = isItDeathDoor(dmgDealt);
        System.out.println(this.getClass().getSimpleName() + " will get" + dmgDealt + " and current hp is: "+currentHP);
        System.out.println(deathCheck);
        if (deathCheck) {
            if (type==DamageType.PHYSICAL) {
                System.out.println("PHYSICAL");
                field.removeFromBattleField(this,true);
            }
            else
                field.removeFromBattleField(this,false);
        }
        return deathCheck;
    }

    @Override
    public int compareTo(Object o) {
        return 0;
    }

    protected short maxHP=20;
    protected short stunResist=100;
    protected short bleedResist=100;
    protected short moveResist=100;
    protected short debuffResist=100;
    protected short blightResist=100;
    protected short armor=0;
    protected short speed=6;
    protected short dodge=10;
    protected short accuracy=100;
    protected short minDamage=9;
    protected short maxDamage = 14;
    protected short critChance = 15;
    protected short currentHP=maxHP;
    private ArrayList<TickedEffects> currentTickedEffects;
    protected ArrayList<Ability> battleAbilities;
    protected short size;
}
