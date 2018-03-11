import java.io.*;
import java.lang.reflect.Field;
import java.lang.reflect.InvocationTargetException;
import java.util.Properties;
import java.util.TreeMap;

public class Factory {
	public static Factory getInstance() {//throws FactoryInvalidInitialisation{
		if(f==null)
			f = new Factory();
		return f;
	}
//	public Unit getUnit(String name){//} throws FactoryCommandNotFoundException {
//
//		Class<?> c;
//		Object unit = null;
//		try {
//			String statsFile = name + "Stats.txt";
//			InputStream is = Factory.class.getClassLoader().getResourceAsStream(statsFile);
//			stats.load(is);
//		}
//		catch (IOException exc) {
//			//		throw new FactoryCommandNotFoundException ("Unknown command");
//			System.out.println("HSDHSDFHSD");
//		}
//		try {
//			c = Class.forName(name);
//			unit = c.getDeclaredConstructor(Properties.class).newInstance(stats);
//		}
//		catch (ClassNotFoundException | NoSuchMethodException | IllegalAccessException | InstantiationException | InvocationTargetException exc) {
//			System.out.println(exc.getMessage()+ "AAAAAAAAAAAAAAAA");
////			Field [] fields = unit.getClass().getSuperclass().getSuperclass().getDeclaredFields();
////			for (Field f:fields) {
////				if (f.getName().equals("armor")) {
////					System.out.println("heh");
////					//f.setAccessible(true);
////					f.set(unit, (short)20);
////				}
//				//f.set(unit,Integer.parseInt(stats.get(f.getName())));
//				//System.out.println(f.getName());
//			}
//			//stats.forEach(unit,(field,value)->unit.getClass().getDefield.);
//
//		return (Unit) unit;
//	}

	public Unit getUnit(String name) throws Exception {
		Class <?> c = Class.forName(name);
		Object obj = c.getDeclaredConstructor().newInstance();
		return (Unit) obj;
	}

//	private Factory() {// throws  FactoryInvalidInitialisation{
//		//commands = new Properties();
//		InputStream is = Factory.class.getClassLoader().getResourceAsStream(configFileName);
//		if (is!=null) {
//			try {
//				commands.load(is);
//			}
//			catch (IOException exc) {
//				//throw new FactoryInvalidInitialisation("Missing config file!");
//			}
//		}
//	}
	private static final String configFileName = "unutstat.txt";//???
	private static Factory f = null;
	private Properties stats = new Properties();
	private Properties abilities = new Properties();
}
