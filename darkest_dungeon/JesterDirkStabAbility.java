import java.util.Scanner;

public class JesterDirkStabAbility extends Ability {
    JesterDirkStabAbility(Unit user) {
        this.user = user;
        setName("Dirk Stab ");
    }
    @Override
    void upgrade() {

    }

    @Override
    boolean isLegal(BattleContext field) {
        //choseTargets(field);
        return true;
    }

    @Override
    public void choseTargets(BattleContext field) {
        targets.clear();
        Scanner in = new Scanner(System.in);
        System.out.println  ("CHOOSE ENEMY TO DIRKSTAB");
        int x = in.nextInt();
       // in.close();
        if (x>3) {
            targets.add(null);
            return;
        }
        Unit target = field.getTargetByIndex(x,true);
        targets.add(0,target);
    }

    @Override
    void using(BattleContext field) {
//        if(isLegal(field)) {
            //choseTargets(field);
            field.changeUnitPosition(user, 1, MoveDirection.FORWARD);
           // boolean isAnyBodyDead;
            user.dealDamage(targets.get(0),0,field);
            //targets.get(0)
        //   return  (isAnyBodyDead) ? targets.get(0) : null;
//        }
    }
}
