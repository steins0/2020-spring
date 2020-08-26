import java.util.Scanner;

public class Main{
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        for(int i = 0;i<10;i++) {
            String charSet = "abcdefg";
            String input = scanner.next();
            ArithmeticEncode arithmeticEncode = new ArithmeticEncode(charSet, input);
        }
    }
}