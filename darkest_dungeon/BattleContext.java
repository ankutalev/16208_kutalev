public interface BattleContext {
    void removeFromBattleField(Unit unit,boolean willBeCorpse);
    void makeTurnQueue();
    void battle();
    byte getUnitPosition(Unit unit);
    boolean isThisPositionHasUnit(byte position);
    boolean tryToEscape();
    void changeUnitPosition(Unit unit, int maxChange, MoveDirection dir);
    Unit getTargetByIndex(int index,boolean isHero);
}
