public class StackTopRevert implements Command {
    @Override
    public void execute(BefungeEnvironment context) {
        context.stackRevert();
    }
}
