public class MulOperation implements Command {
    @Override
    public void execute(BefungeEnvironment context) {
        context.arithOperations(Operations.MUL);
    }
}
