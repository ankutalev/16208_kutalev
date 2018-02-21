public class IfMoveDown implements Command {
    @Override
    public void execute(BefungeEnvironment context) {
        context.ifMove(Direction.UP);
    }
}
