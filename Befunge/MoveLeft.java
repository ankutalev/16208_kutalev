public class MoveLeft implements Command{
    @Override
    public void execute(BefungeEnvironment context) {
        context.move(Direction.LEFT);
    }
}
