public class MoveDown implements Command {
    @Override
    public void execute(BefungeEnvironment context) {
        context.move(Direction.DOWN);
    }
}
