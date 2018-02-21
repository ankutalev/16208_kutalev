public class SumOperation implements Command {
    @Override
    public void execute(BefungeEnvironment context) {
        context.arithOperations(Operations.SUM);
    }
}
