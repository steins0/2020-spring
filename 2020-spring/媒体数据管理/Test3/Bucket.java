import java.util.ArrayList;

public class Bucket {
    private ArrayList<Lvector> data;


    public void add(Lvector lv){
        data.add(lv);
    }



    public ArrayList<Lvector> getData() {
        return data;
    }

    public Bucket(){
        this.data = new ArrayList<Lvector>();
    }
}
