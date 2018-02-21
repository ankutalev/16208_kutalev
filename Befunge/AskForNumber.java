public class AskForNumber implements Command {
    @Override
    public void execute(BefungeEnvironment context) {
        context.askForNumber();
    }
}
