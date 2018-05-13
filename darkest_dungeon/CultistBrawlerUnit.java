public class CultistBrawlerUnit extends Unit {
   // CultistBrawlerUnit(String data) {
   //     super(data);
   // }
    CultistBrawlerUnit() {
        maxHP = 15;
        speed = 5;
        minDamage = 4;
        maxDamage = 8;
    }

    @Override
    public void battleAction(BattleContext field) {
        System.out.println("YA POHODIL");
    }

    @Override
    public void moveBack(BattleContext field) {

    }

//    @Override
//    protected void deathWithCorpse() {
//
//    }

    @Override
    protected void deathWithOutCorpse() {

    }

//    @Override
//    public void skipTurn() {
//
//    }

    @Override
    public void moveForward(BattleContext field) {

    }

}
