public class PrintTopAsSymbol implements Command {
    @Override
    public void execute(BefungeEnvironment context) {
        context.printTopAsSymbol();
    }
}
