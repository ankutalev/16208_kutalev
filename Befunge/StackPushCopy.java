public class StackPushCopy implements Command {
    @Override
    public void execute(BefungeEnvironment context) {
        context.push();
    }
}
