public class GetFromStack implements Command {
    @Override
    public void execute(BefungeEnvironment context) {
        context.getFromStack();
    }
}
