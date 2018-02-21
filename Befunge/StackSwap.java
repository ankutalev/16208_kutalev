public class StackSwap implements Command {
    @Override
    public void execute(BefungeEnvironment context) {
        context.swap();
    }
}
