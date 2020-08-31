import java.net.*;
import java.io.*;
import java.util.Scanner;

public class Client {
    public static void main(String[] args) {
        DatagramSocket socket = null;
        String pack = method();
        try{
            socket = new DatagramSocket();
            InetAddress host = InetAddress.getByName("127.0.0.1");
            int port = 677;
            byte[] by = pack.getBytes();
            DatagramPacket request = new DatagramPacket(by, by.length,host,port);
            socket.send(request);
            byte[] buf = new byte[1000];
            DatagramPacket receive = new DatagramPacket(buf, buf.length);
            socket.receive(receive);
            System.out.println("anwser:"+new String(receive.getData()));
        }catch(SocketException e){
            System.out.println("socket:"+e.getMessage());
        }catch(IOException e){
            System.out.println("IO:"+e.getMessage());
        }finally{
            if(socket != null)socket.close();
        }
    }

    private static String method() {
        String str = null;
        Scanner sc = new Scanner(System.in);
        System.out.println("choose the operator: \n1.+\n2.-\n3.*\n4./");
        int num0 = sc.nextInt();
        System.out.println("input first number:");
        int num1 = sc.nextInt();
        System.out.println("input second number:");
        int num2 = sc.nextInt();
        switch(num0){
            case 1:
            str = String.valueOf(num1)+"+"+String.valueOf(num2);
            break;
            case 2:
            str = String.valueOf(num1)+"-"+String.valueOf(num2);
            break;
            case 3:
            str = String.valueOf(num1)+"*"+String.valueOf(num2);
            break;
            case 4:
            str = String.valueOf(num1)+"/"+String.valueOf(num2);
            break;
        }
        sc.close();
        return str;
    }
}
