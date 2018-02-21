public class AskForSymbol implements Command {
    @Override
    public void execute(BefungeEnvironment context) {
        context.askForSymbol();
    }
}
