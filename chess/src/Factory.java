import java.io.IOException;
import java.io.InputStream;
import java.util.Properties;


public class Factory {
    public static Factory getInstance() throws FactoryInvalidInitialisation {
        if (f == null)
            f = new Factory();
        return f;
    }

    public Figure getFigure(String id) throws FactoryFigureNotFoundException {
        Class<?> c;
        Object comm;
        try {
            c = Class.forName(Figures.getProperty(id));
            comm = c.getDeclaredConstructor().newInstance();
        } catch (Exception exc) {
            throw new FactoryFigureNotFoundException("Unknown Figure");
        }
        return (Figure) comm;
    }

    private Factory() throws FactoryInvalidInitialisation {
        Figures = new Properties();
        InputStream is = Factory.class.getClassLoader().getResourceAsStream(configFileName);
        if (is != null) {
            try {
                Figures.load(is);
            } catch (IOException exc) {
                throw new FactoryInvalidInitialisation("Missing config file!");
            }
        }
    }

    private static final String configFileName = "config.properties";
    private static Factory f = null;
    private Properties Figures;
}
