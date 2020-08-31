
import java.rmi.Remote;
import java.rmi.RemoteException;
import java.util.List;

public interface bookcal extends Remote {

    public boolean add(book a) throws RemoteException;

    public book queryByID(int id) throws RemoteException;

    public boolean delete(int id) throws RemoteException;

    public List<book> queryByName(String name) throws RemoteException;
}