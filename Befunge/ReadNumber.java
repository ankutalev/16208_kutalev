public class ReadNumber implements Command {
    @Override
    public void execute(BefungeEnvironment context) {
        context.getNumber();
    }
}
