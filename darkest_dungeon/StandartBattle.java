import java.util.*;
import java.util.concurrent.ThreadLocalRandom;

public class StandartBattle implements BattleContext {

//    StandartBattle (ArrayList heroes,Location loc, ExpeditionLevel lvl) {
//          todo: генерировать стандартные наборы юнитов через фабрику исходя из уровня локации
//    }
    StandartBattle (ArrayList<Unit> heroes,ArrayList<Unit> enemies) {
        this.enemies = enemies;
        this.heroes = heroes;
    }

    @Override
    public void battle() {
        System.out.println("BATTLE STARTS");
        int turnCounter = 1;
        while (battleIsOn()) {
            System.out.println("AND NOW THE"+turnCounter + " TURN");
            makeTurnQueue();
            System.out.println("TURN QUEUE SIZE: =" +turnPriority.size());
            //todo: need new battle algo : if unit is dead by effects he still being on battlefiled
//            turnPriority.forEach((hero,speed)-> {
//                hero.info();
//                hero.battleTurn(this);
//            });
            while(!turnPriority.isEmpty()&&battleIsOn()) {
                turnPriority.remove().battleTurn(this);
            }
            turnCounter++;
        }

        //todo: reinforcemnt after turn for reinforcement
    }


    @Override
    public void removeFromBattleField(Unit unit,boolean willBeCorpse) {
        turnPriority.remove(unit);
        if (unit.isHero()) {
            heroes.remove(unit);
        }
        else {
            if (willBeCorpse) {
                //enemies.set(enemies.indexOf(unit),new UnitCorpse) //todo: make units corpse
            }
            else
                enemies.remove(unit);
        }

    }

    @Override
    public void changeUnitPosition(Unit unit, int maxChange, MoveDirection dir) {
//            int startIndex = (unit.isHero()) ? heroes.indexOf(unit) : enemies.indexOf(unit);
//            for (int i = 0; i< maxChange;i++) {
//            }
    }

//    public void moveUnitForward(Unit unit) {
//        int index;
//        if (enemies.contains(unit)) {
//            index = enemies.indexOf(unit);
//            enemies.
//        }
//    }

    @Override
    public byte getUnitPosition (Unit unit) {
        byte position;

        if (unit.isHero()) {
            position = helpIndexGetter(heroes,unit);
        }
        else {
            position = helpIndexGetter(enemies,unit);
        }
        return position;
    }

    @Override
    public Unit getTargetByIndex(int index,boolean isHero) {
        return (isHero) ? enemies.get(index) : heroes.get(index);
    }

    @Override
    public void makeTurnQueue() {
      //  int thisTurnSpeed;
     //   turnPriority.clear();
       // for (Unit x:heroes) {
        //    thisTurnSpeed= x.getSpeed() + ThreadLocalRandom.current().nextInt(0,7);
            turnPriority.addAll(heroes);
        //}
       // for (Unit en: enemies) {
         //   thisTurnSpeed= en.getSpeed() + ThreadLocalRandom.current().nextInt(0,7);
            turnPriority.addAll(enemies);
        //}
    }
    @Override
    public boolean isThisPositionHasUnit(byte position) {

        return false;
    }

    @Override
    public boolean tryToEscape() {
        return false;
    }

    private byte helpIndexGetter (ArrayList<Unit> units,Unit unit) {
        for (byte i = 0 ; i < units.size();i++)
            if (units.get(i).equals(unit))
                return i;
        throw new RuntimeException("kek"); //todo: clean this shit pls
    }

    private boolean battleIsOn() {
        return !(enemies.isEmpty() || heroes.isEmpty());
    }

    private final  int TURNS_COUNTER_BEFORE_REIFORCEMENT = 10;
    private ArrayList<Unit> heroes;
    private ArrayList<Unit> enemies;
   // private Map <Unit,Integer> turnPriority = new HashMap<>();
    private PriorityQueue<Unit> turnPriority = new PriorityQueue<>(new UnitSpeedComparator());
}
