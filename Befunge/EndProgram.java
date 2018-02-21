public class EndProgram implements Command {
    @Override
    public void execute(BefungeEnvironment context) {
        context.endProgram();
    }
}
