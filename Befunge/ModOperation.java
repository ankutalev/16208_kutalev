public class ModOperation implements Command {
    @Override
    public void execute(BefungeEnvironment context) {
        context.arithOperations(Operations.MOD);
    }
}
