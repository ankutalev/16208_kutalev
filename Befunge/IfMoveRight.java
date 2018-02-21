public class IfMoveRight implements Command {
    @Override
    public void execute(BefungeEnvironment context) {
        context.ifMove(Direction.LEFT);
    }
}
