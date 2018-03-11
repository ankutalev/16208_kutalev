import java.util.Scanner;

public class JesterHarvestAbility extends Ability {

        JesterHarvestAbility(Unit user) {
            this.user = user;
            setName("Harvest");
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
            System.out.println  ("CHOOSE ENEMY TO HARVEST");
            int x = in.nextInt();
            if (x>3) {
                targets.add(null);
                return;
            }
            Unit target = field.getTargetByIndex(x,true);
            targets.add(0,target);
        }

        @Override
        void using(BattleContext field) {
            user.dealDamage(targets.get(0),0.5,field);
            targets.get(0).takeTickedEffect(new BleedEffect(4,3));
         //   isAnyBodyDead = user.dealDamage(targets.get(0)); //:todo add ddmg penalty
         //   if (isAnyBodyDead) {
         //       field.removeFromBattleField(targets.get(0));
         //   }
            //   return  (isAnyBodyDead) ? targets.get(0) : null;
//        }
        }
    }
