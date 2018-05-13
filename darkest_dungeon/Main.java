import java.util.ArrayList;

public class Main {

    public static void main(String[] args) {

        //Unit jester = new JesterHero("huy");
        Unit jester = null;
        Unit cultist = null;
        try {

             jester = Factory.getInstance().getUnit("JesterHero");
             cultist = Factory.getInstance().getUnit("CultistBrawlerUnit");
        }
        catch (Exception exc) {

        }
        System.out.println(jester.getSpeed());
//        Unit cultist = new CultistBrawlerUnit("huy");
        if (jester.isHero())
            System.out.println("JESTER IS HERO!!!!");
        if (!cultist.isHero())
            System.out.println("CULTIST ISTN HERO!!!");
//
        ArrayList<Unit> heroes = new ArrayList<>();
        heroes.add(0,jester);
        ArrayList <Unit> enemies = new ArrayList<>();
        enemies.add(0,cultist);
        BattleContext battle = new StandartBattle(heroes,enemies);
        System.out.println(heroes.isEmpty());
        battle.battle();

    }

}
