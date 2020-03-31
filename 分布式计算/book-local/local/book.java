import java.io.Serializable;

public class book implements Serializable {

    /**
     *
     */
    private static final long serialVersionUID = -2484964814718917667L;
    private int id;
    private String name;

    public book() {
    }

    public book(int id, String name) {
        this.id = id;
        this.name = name;
    }

    int getid() {
        return id;
    }

    String getname() {
        return name;
    }
}