public class ReadString implements Command {
    @Override
    public void execute(BefungeEnvironment context) {
        context.getStringOfASCI();
    }
}
