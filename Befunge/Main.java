import java.io.IOException;
public class Main {
	public static void main(String[] args) {
		Befunge x = new Befunge_93();
		try {
			x.setupTable();
		}
		catch (IOException exc) {
			System.out.println(exc.getMessage());
			return;
		}
		x.run();
	}
}
