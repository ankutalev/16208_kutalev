public class SubOperation implements  Command {
    @Override
    public void execute(BefungeEnvironment context) {
        context.arithOperations(Operations.SUB);
    }
}
