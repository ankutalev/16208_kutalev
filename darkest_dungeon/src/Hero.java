import java.util.ArrayList;
import java.util.Scanner;
import java.util.concurrent.ThreadLocalRandom;

public abstract class Hero extends Unit {
    Hero(String data) {
        super(data);
        campAbilities= new ArrayList<>();
        battleAbilities = new ArrayList<>();
    }

    @Override
    public void takeDamage(short dmg, DamageType type) {
        short dmgDealt=dmg;
        short armor = getArmor();
        if (type !=DamageType.PURE) {
            dmgDealt = (armor==0) ? dmgDealt : (short)(armor *dmg / 100);
        }
        if (type==DamageType.CRITICAL) {
            stressIncreased(this,CRIT_STRESS_INCREASE_CONST);
        }
        if(isItDeathDoor(dmgDealt)&&deathBlowCheck()) {
            deathWithCorpse();
        }

    }

    @Override
    public void battleAction(BattleContext field) {
        System.out.println("I am hero!");
        int choosen = chooseAbility(field);
        if (choosen==-1)
            skipTurn();
        else
            battleAbilities.get(choosen).using(field);
    }
    //******************************DANGER!!! CANCER METHOD USE ONLY FOR 1ST TIME DEBUGGING*******
    private int chooseAbility(BattleContext field) {
        boolean hasLegalAbility = false;
        for (Ability skill:battleAbilities) {
            if (skill.isLegal(field)) {
                hasLegalAbility = true;
            }
        }
        if (!hasLegalAbility)
            return -1;
        else {
            Scanner in = new Scanner(System.in);
            int x = in.nextInt();
            if (!battleAbilities.get(x).isLegal(field)) {
                in.close();
                System.out.println("You can't choose this ability!");
                chooseAbility(field);
            } else
                return x;
        }
        return -1;
    }
    //*****************************************************************************************
    @Override
    public void skipTurn() {
        System.out.println(name+" Skipped turn!");
    }
    private  void faithCheck() {
        int check = ThreadLocalRandom.current().nextInt(0,100);
        mind = (check > deathBlowResist)? MindStatus.VIRTOUSED : MindStatus.AFFICTIONED;
    }
    protected boolean deathBlowCheck() {
        int check = ThreadLocalRandom.current().nextInt(0,100);
        return  check > deathBlowResist;
    }
    public void stressIncreased(Hero target,byte value) {
         target.stress+=value;
         if (target.stress>=STRESS_AFFICTION_CONST&&target.mind == MindStatus.NORMAL)
             faithCheck();
         if (target.stress>=STRESS_HEART_ATTACK_CONST&& deathBlowCheck())
             deathWithOutCorpse();
         else
             target.stress=STRESS_HEART_ATTACK_CONST;
    }

    public short getStress() {
        return stress;
    }

    private ArrayList<Ability> campAbilities;
    private ArrayList<Ability> battleAbilities;
    private short deseaseResist=20;
    private short deathBlowResist=63;
    private short stress=0;
    private short trapChance=20;
    private MindStatus mind = MindStatus.NORMAL;
    private String name = "Default Anonymous";
    private STATUS status = STATUS.ALIVE;
    final byte CRIT_STRESS_INCREASE_CONST = 7;
    final short STRESS_AFFICTION_CONST = 100;
    final short STRESS_HEART_ATTACK_CONST = 200;
}
