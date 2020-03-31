import java.rmi.RemoteException;
import java.rmi.server.UnicastRemoteObject;
import java.util.ArrayList;
import java.util.List;

public class bookcalmpl extends UnicastRemoteObject implements bookcal {

    /**
     *
     */
    private static final long serialVersionUID = -414909245884949393L;
    private static List<book> books = new ArrayList<book>();
    private static List<book> booknew = new ArrayList<book>();
    private static book bo;
    private static int len;
    protected bookcalmpl() throws RemoteException {
        super();
        // TODO Auto-generated constructor stub
    }

    @Override
    public boolean add(book a) throws RemoteException {
        books = bookserver.booksend();
        books.add(a);
        bookserver.bookget(books);
        System.out.println("book count"+books.size()+"book id:"+a.getid()+"  book name:"+a.getname());
        // TODO Auto-generated method stub
        return true;
    }

    @Override
    public boolean delete(int id) throws RemoteException {
        books = bookserver.booksend();
        len = books.size();
        for(int i= 0;i<len;i++){
            bo = books.get(i);
            if(id == bo.getid()){
                books.remove(i);
                bookserver.bookget(books);
                System.out.println("delete successed!");
                return true;
            }
        }
        System.out.println("delete error or the id is no book there");
        // TODO Auto-generated method stu
        return false;
    }

    @Override
    public List<book> queryByName(String name) throws RemoteException {
        books = bookserver.booksend();
        len = books.size();
        for(int i= 0;i<len;i++){
            bo = books.get(i);
            if(name == bo.getname()){
                booknew.add(bo);
            }
        }
        System.out.println("booklist successed!");
        // TODO Auto-generated method stub
        return booknew;
    }

    @Override
    public book queryByID(int id) throws RemoteException {
        books = bookserver.booksend();
        System.out.println("book count:"+books.size());
        book a =new book(-1,"err");
        len = books.size();
        for(int i= 0;i<len;i++){
            bo = books.get(i);
            System.out.println(bo.getid());
            if(id == bo.getid()){
                System.out.println("find successed!");
                return bo;
            }
        }
        System.out.println("find error or the id is no book there");
        // TODO Auto-generated method stub
        return a;
    }
}