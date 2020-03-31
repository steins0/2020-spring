import java.util.regex.*;
public class march{
    public static void main(String[] args) {
        String str = "13-2";
        String st = "(.*)(\\-)(.*)";

        Pattern p = Pattern.compile(st);
        Matcher m = p.matcher(str);
        if(m.find())
        {
            System.out.println(m.group(0)+"\n"+m.group(1)+"\n"+m.group(2)+"\n"+m.group(3));
        }else{
            System.out.println("no march"+str);
        }
    }
}