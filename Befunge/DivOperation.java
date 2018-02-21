public class DivOperation implements Command {
    @Override
    public void execute(BefungeEnvironment context) {
        context.arithOperations(Operations.DIV);
    }
}
