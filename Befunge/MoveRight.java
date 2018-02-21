public class MoveRight implements Command {
    @Override
    public void execute(BefungeEnvironment context) {
     context.move(Direction.RIGHT);
    }
}
