import java.lang.reflect.Field;
import java.util.ArrayList;
import java.util.Properties;
import java.util.Scanner;
import java.util.concurrent.ThreadLocalRandom;

public abstract class Hero extends Unit {
    Hero(Properties data) {
        super(data);
        Field[] fields = getClass().getDeclaredFields();
        System.out.println(fields.length);
        for (Field f: fields) {
            if (data.containsKey(f.getName())) {
                f.setAccessible(true);
                try {
                    f.set(this, data.get(f.getName()));
                }
                catch (Exception exc) {
                    System.out.println("WTO-TO SLUCHILOS' V NASHIH LESAH!");
                }
            }
        }
        campAbilities= new ArrayList<>();
        battleAbilities = new ArrayList<>();
    }

    Hero() {
        super();
        campAbilities= new ArrayList<>();
       // battleAbilities = new ArrayList<>();
    }


    @Override
    public boolean takeDamage(short dmg, DamageType type,BattleContext field) {
        short dmgDealt=dmg;
        short armor = getArmor();
        if (type !=DamageType.PURE) {
            dmgDealt = (armor==0) ? dmgDealt : (short)(armor *dmg / 100);
        }
        if (type==DamageType.CRITICAL) {
            Hero[] tmp = new Hero[1];
            tmp[0] = this;
            stressIncreased(tmp,CRIT_STRESS_INCREASE_CONST);
        }
        boolean deathCheck = isItDeathDoor(dmgDealt);
        if(deathCheck&&deathBlowCheck()) {
            field.removeFromBattleField(this,false);
        }
        return deathCheck;

    }




    @Override
    public void battleAction(BattleContext field) {
        System.out.println("I am hero!");
        getAvailibleAbilities(field);
      //  if (availibleAbilities.isEmpty())
            //skipTurn();
        int choosen = chooseAbility(field);
//        if (choosen==-1)
//            skipTurn();
       // else {
            Ability current = battleAbilities.get(choosen);
            System.out.println(this.getClass().getSimpleName() + "  choose  " + current.getClass().getSimpleName() );
            current.choseTargets(field);
            current.using(field);
        //}
    }



    //******************************DANGER!!! CANCER METHOD USE ONLY FOR 1ST TIME DEBUGGING*******
    private int chooseAbility(BattleContext field) {

          System.out.println("Availible abilities: ");
          int i = 0;
        for (Ability abil: availibleAbilities) {
            System.out.println(abil.getName() + i);
            i++;
        }

//        boolean hasLegalAbility = false;
//
//        for (Ability skill:battleAbilities) {
//            if (skill.isLegal(field)) {
//                hasLegalAbility = true;
//            }
//        }
//        System.out.println(hasLegalAbility);
//        if (!hasLegalAbility) {
//            return -1;
//        }
//        else {
//            //System.out.println("tuta");
            Scanner in = new Scanner(System.in);
            int x = in.nextInt();
//            if (!battleAbilities.get(x).isLegal(field)) {
//                in.close();
//                System.out.println("You can't choose this ability!");
//                chooseAbility(field);
//            } else
                return x;
//        }
//        return -1;
    }
    //*****************************************************************************************


//    @Override
//    public void skipTurn() {
//        System.out.println(name+" Skipped turn!");
//    }

    private  void faithCheck() {
        int check = ThreadLocalRandom.current().nextInt(0,100);
        mind = (check > deathBlowResist)? MindStatus.VIRTOUSED : MindStatus.AFFICTIONED;
    }



    protected boolean deathBlowCheck() {
        int check = ThreadLocalRandom.current().nextInt(0,100);
        return  check > deathBlowResist;
    }


    public void stressIncreased(Hero[] targets,byte value) {
        for (Hero target: targets) {
            target.stress += value;
            if (target.stress >= STRESS_AFFICTION_CONST && target.mind == MindStatus.NORMAL)
                faithCheck();
            if (target.stress >= STRESS_HEART_ATTACK_CONST && deathBlowCheck())
                deathWithOutCorpse();
            else
                target.stress = STRESS_HEART_ATTACK_CONST;
        }
    }

    public short getStress() {
        return stress;
    }


    private void getAvailibleAbilities(BattleContext field) {
        availibleAbilities.clear();
        for (Ability abil:battleAbilities) {
            if (abil.isLegal(field))
                availibleAbilities.add(abil);
        }
    }

    private ArrayList<Ability> campAbilities;
    //protected ArrayList<Ability> battleAbilities;
    protected ArrayList<Ability> availibleAbilities = new ArrayList<>();
    private short deseaseResist=20;
    private short deathBlowResist=63;
    private short stress=0;
    protected short trapChance=20;
    private MindStatus mind = MindStatus.NORMAL;
    protected String name = "Default Anonymous";
    private Status status = Status.ALIVE;
    private final byte CRIT_STRESS_INCREASE_CONST = 7;
    private final short STRESS_AFFICTION_CONST = 100;
    private final short STRESS_HEART_ATTACK_CONST = 200;
}
