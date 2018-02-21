public class MoveRandom implements Command {
    @Override
    public void execute(BefungeEnvironment context) {
        context.move(Direction.RANDOM);
    }
}
