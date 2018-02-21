public class MoveUp implements Command {
    @Override
    public void execute(BefungeEnvironment context) {
        context.move(Direction.UP);
    }
}
