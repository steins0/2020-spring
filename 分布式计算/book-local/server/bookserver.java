import java.rmi.registry.LocateRegistry;
import java.rmi.registry.Registry;
import java.util.ArrayList;
import java.util.List;


public class bookserver {
    private static List<book> books = new ArrayList<book>();
    public static void main(String[] args) throws Exception {
        
        try {
            String name = "book";
            bookcalmpl engine = new bookcalmpl();
            Registry registry = LocateRegistry.getRegistry("127.0.0.1", 1099);
            System.out.println("Registering book Object");
            registry.bind(name, engine);
        } catch (Exception e) {
            System.err.println("Exception:" + e);
            e.printStackTrace();
        }
    }

    public static void bookget(List<book> book){books = book;}
    public static List<book> booksend(){return books;}
}