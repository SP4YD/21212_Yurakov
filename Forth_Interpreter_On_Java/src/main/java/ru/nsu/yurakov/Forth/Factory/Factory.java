package ru.nsu.yurakov.Forth.Factory;

import org.apache.logging.log4j.LogManager;
import org.apache.logging.log4j.Logger;
import ru.nsu.yurakov.Forth.ForthCommands.ForthCommands;
import ru.nsu.yurakov.Forth.ForthInterpreter.ForthInterpreter;

import java.io.IOException;
import java.io.InputStream;
import java.util.HashMap;
import java.util.Properties;

public class Factory {

    /** Return factory
     * @return the only shared instance of the factory
     * @throws RuntimeException If it was not possible to create a factory
     */
    public static Factory GetFactory() throws RuntimeException {
        LOGGER.info("Was launched GetFactory");
        if (Instance == null) {
            Instance = new Factory();
        }
        return Instance;
    }

    private Factory() throws RuntimeException {
        LOGGER.info("Was launched Factory Constructor");
        Path = new Properties();
        CreatedInstances = new HashMap<>();
        try (InputStream file = ForthCommands.class.getClassLoader().getResourceAsStream(Config)) {
            Path.load(file);
        } catch (IOException ex) {
            throw new RuntimeException("in Factory.construct - " + ex.getMessage());
        }
    }

    /** Creates an instance by the passed name
     * @param NameInstance The name by which the instance will be searched
     * @return Instance
     * @throws ClassNotFoundException If it was not possible to create an instance with the given name
     */
    public Object CreateInstance(String NameInstance) throws ClassNotFoundException {
        LOGGER.info("Was launched CreateInstance(" + NameInstance + ")");
        try {
            Class<?> needClass = null;
            if (CreatedInstances.containsKey(NameInstance)) {
                needClass = CreatedInstances.get(NameInstance);
            } else {
                needClass = Class.forName(Path.getProperty(NameInstance));
            }

            CreatedInstances.put(NameInstance, needClass);

            return needClass.getDeclaredConstructor().newInstance();
        } catch (Exception ex) {
            throw new ClassNotFoundException("in CreateInstance with the name - \"" + NameInstance + "\"");
        }
    }

    private static Factory Instance = null;
    private final String Config = "PathFile.cfg";
    private Properties Path = null;
    private HashMap<String, Class<?>> CreatedInstances = null;

    private static final Logger LOGGER = LogManager.getLogger(Factory.class);
}