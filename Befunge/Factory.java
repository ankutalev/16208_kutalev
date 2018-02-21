import java.io.*;
import java.util.Properties;
import java.util.TreeMap;

public class Factory {
	public static Factory getInstance(){
		if(f==null) 
			f = new Factory();
		return f;
	}
	public Command getCommand  (String id) throws ClassNotFoundException {
        Class<?> c;
        Object comm;
	    try {
             c = Class.forName(commands.getProperty(id));
             comm = c.getDeclaredConstructor().newInstance();
        }
        catch (Exception exc) {
	        throw new ClassNotFoundException("Unknown command");
        }
		return (Command) comm;
	}

	private Factory() {
	       commands = new Properties();
	       InputStream is = Factory.class.getClassLoader().getResourceAsStream(configFileName);
	       if (is!=null) {
			try {
				commands.load(is);
			}
			catch (IOException exc) {
				System.out.println("Missing config file!");
			}
		} 
		 
	}
	private final String configFileName = "config.txt";
	private static Factory f = null;
	private Properties commands;
}
