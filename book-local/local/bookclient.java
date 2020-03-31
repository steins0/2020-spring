import java.util.ArrayList;
import java.util.List;
import java.util.Scanner;
import java.rmi.registry.LocateRegistry;
import java.rmi.registry.Registry;

public class bookclient {
    public static void main(String args[]) {

        try {
            Scanner sc = new Scanner(System.in);
            book a;
            int id;
            String bookname;
            boolean flag = false;
            List<book> books = new ArrayList<book>();
            int len;
            String name = "book";
            String serverIP = "127.0.0.1";
            int serverPort = 1099;
            Registry registry = LocateRegistry.getRegistry(serverIP, serverPort);
            bookcal mycalc = (bookcal) registry.lookup(name);
            while (true) {
                System.out.println("choose the method you want(by number):");
                System.out.println("1.add book");
                System.out.println("2.find book");
                System.out.println("3.delete book");
                System.out.println("4.return booklist");
                int num = sc.nextInt();
                switch (num) {
                    case 1:
                        System.out.println("input the book id(the id can not be -1):");
                        id = sc.nextInt();
                        System.out.println("input the book name:");
                        bookname = sc.next();
                        a = new book(id, bookname);
                        flag = mycalc.add(a);
                        if (flag == true)
                            System.out.println("book add successed!");
                        else
                            System.out.println("book add error");
                        break;
                    case 2:
                        System.out.println("input the book id:");
                        id = sc.nextInt();
                        a = mycalc.queryByID(id);
                        if (a.getid() == -1)
                            System.out.println("this id is no book oe find error");
                        else
                            System.out.println("book name:" + a.getname());
                        break;
                    case 3:
                        System.out.println("input the book id:");
                        id = sc.nextInt();
                        flag = mycalc.delete(id);
                        if (flag == true)
                            System.out.println("book delete successed!");
                        else
                            System.out.println("book delete error or there is no this id book");
                        break;
                    case 4:
                        System.out.println("input the book name:");
                        bookname = sc.next();
                        books = mycalc.queryByName(bookname);
                        if (books.size() == 0)
                            System.out.println("there is no this name book or error");
                        else {
                            len = books.size();
                            for (int i = 0; i < len; i++) {
                                a = books.get(i);
                                System.out.println("the book id:" + a.getid());
                            }
                        }
                        break;
                }
            }
        } catch (Exception e) {
            System.err.println("??? exception:");
            e.printStackTrace();
        }
    }
}