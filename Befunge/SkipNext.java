public class SkipNext implements Command {
    @Override
    public void execute(BefungeEnvironment context) {
        context.skip();
    }
}
