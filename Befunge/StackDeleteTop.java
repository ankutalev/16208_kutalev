public class StackDeleteTop implements Command {
    @Override
    public void execute(BefungeEnvironment context) {
        context.deleteTop();
    }
}
