package Factory;

import java.io.InputStream;
import java.lang.reflect.Constructor;
import java.util.HashMap;
import java.util.Properties;

import ForthCommands.ForthCommands;

public class Factory {

    public static Factory GetFactory() {
        if (Instance == null) {
            Instance = new Factory();
        }
        return Instance;
    }

    private Factory() {
        Path = new Properties();
        CreatedInstances = new HashMap<>();
        try {
            InputStream file = ForthCommands.class.getClassLoader().getResourceAsStream(Config);
            Path.load(file);
        } catch(Exception ex) {
            System.out.println("Error in Factory.construct");
        }
    }

    public Object CreateInstance(String NameInstance) {
        if (CreatedInstances.containsKey(NameInstance)) {
            return CreatedInstances.get(NameInstance);
        }
        try {
            Class<?> needClass = Class.forName(Path.getProperty(NameInstance));
            Class<?>[] arg = null;
            Constructor<?> construct = needClass.getConstructor(arg);
            Object instance = construct.newInstance();
            CreatedInstances.put(NameInstance, instance);
            return instance;
        } catch(Exception ex) {
            System.out.println("Error in Factory");
            return null;
        }
    }

    private static Factory Instance = null;
    private final String Config = "Factory\\PathFile.cfg";
    private Properties Path = null;
    private HashMap<String, Object> CreatedInstances = null;
}