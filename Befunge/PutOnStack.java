public class PutOnStack implements Command {
    @Override
    public void execute(BefungeEnvironment context) {
        context.putOnStack();
    }
}
