import java.io.IOException;
import java.net.DatagramPacket;
import java.net.DatagramSocket;
import java.net.InetAddress;
import java.util.concurrent.BlockingQueue;
import java.util.concurrent.LinkedBlockingQueue;
import java.util.regex.*;


public class Server {
    static Info info = new Info();

    public static void main(String[] args) {
        Received R1 = new Received(info);
        Send S1 = new Send(info);
        R1.start();
        S1.start();
    }

    public static void callback(Info info1) {
        info = info1;
    }
    public static Info callsend(){
        return info;
    }
}

class Info {
    boolean flag1 = false;
    int port = 677;
    int portsend = 0 ;
    InetAddress address = null;
    DatagramSocket socket;
    byte[] buf1 = new byte[1000];
    byte[] buf2 = new byte[1000];
    @SuppressWarnings("unchecked")
    BlockingQueue<String> blockingQueue = new LinkedBlockingQueue(5);
    int[] num = new int[4];

    void ipinfo(int port,InetAddress address){
        this.portsend = port;
        this.address = address;
    }
    int Port(){return port;}
    int ports(){return this.portsend;}
    InetAddress Address(){return address;}

    void flagn1(Boolean flag) {
        flag1 = flag;
    }

    boolean Flag1() {
        return flag1;
    }

    void soc(DatagramSocket socket) {
        this.socket = socket;
    }

    DatagramSocket Soc() {
        return socket;
    }


    byte[] Bye() {
        return buf2;
    }

    void bye(byte[] buf) {
        this.buf2 = buf;
    }

    BlockingQueue<String> Blo() {
        return blockingQueue;
    }

    void Count(int i) {
        num[i]++;
    }
    int[] Num(){return num;}
}

class Received extends Thread {
    private DatagramSocket socket;
    byte[] buf1 = new byte[1000];
    DatagramPacket packet = new DatagramPacket(buf1, buf1.length);
    DatagramPacket packet2 =null;
    int port = 677;
    private Info info;

    Received(Info info) {
        System.out.println("Server creat");
        this.info = info;
        try {
            socket = new DatagramSocket(port);
            info.soc(socket);
        } catch (IOException e) {
            e.printStackTrace();
        }
    };

    public void run() {
        try {
            System.out.println("server start");
            while (true) {
                socket.receive(packet);
                info.bye(buf1);
                InetAddress address = packet.getAddress();
                int port = packet.getPort();
                info.ipinfo(port, address);
                Server.callback(info);
                buf1 = new byte[1000];
                March m1 = new March();
                m1.start();
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}

class March extends Thread {
    private BlockingQueue<String> queue;
    private byte[] buf2 = new byte[1000];
    private DatagramPacket packet2 = null;
    private Info info;
    private boolean flag = false;

    March() {
        info = Server.callsend();
        System.out.println("march creat");
        this.queue = info.Blo();
    }

    public void run() {
        buf2 = info.Bye();
        String infoma = new String(buf2).trim();
        try {
            queue.put(infoma);
        } catch (InterruptedException e) {
            e.printStackTrace();
        }
        System.out.println("march start: " + infoma+" end");
        int num1, num2, ans = 0;
        String st1 = "(.*)(\\-)(.*)";
        String st2 = "(.*)(\\+)(.*)";
        String st3 = "(.*)(\\*)(.*)";
        String st4 = "(.*)(\\/)(.*)";
        Pattern p1 = Pattern.compile(st1);
        Pattern p2 = Pattern.compile(st2);
        Pattern p3 = Pattern.compile(st3);
        Pattern p4 = Pattern.compile(st4);
        Matcher m1 = p1.matcher(infoma);
        Matcher m2 = p2.matcher(infoma);
        Matcher m3 = p3.matcher(infoma);
        Matcher m4 = p4.matcher(infoma);
        if (m1.find()) {
            num1 = Integer.valueOf(m1.group(1)).intValue();
            num2 = Integer.valueOf(m1.group(3)).intValue();
            ans = num1 - num2;
            System.out.println(ans);
            info.Count(1);
        }
        if (m2.find()) {
            num1 = Integer.valueOf(m2.group(1)).intValue();
            num2 = Integer.valueOf(m2.group(3)).intValue();
            ans = num1 + num2;
            info.Count(0);
        }
        if (m3.find()) {
            num1 = Integer.valueOf(m3.group(1)).intValue();
            num2 = Integer.valueOf(m3.group(3)).intValue();
            ans = num1 * num2;
            info.Count(2);
        }
        if (m4.find()) {
            num1 = Integer.valueOf(m4.group(1)).intValue();
            num2 = Integer.valueOf(m4.group(3)).intValue();
            ans = num1 / num2;
            info.Count(3);
        }
        String send = "anwser:" + String.valueOf(ans);
        System.out.println(send);
        buf2 = send.getBytes();
        info.bye(buf2);
        flag = true;
        info.flagn1(flag);
        System.out.println(ans);
        Server.callback(info);
        try {
            queue.take();
        } catch (InterruptedException e) {
            e.printStackTrace();
        } // 清楚队列
    }
}

class Send extends Thread {
    private DatagramSocket socket = null;
    private byte[] buf2 = new byte[1000];
    private DatagramPacket packet2 = null;
    private Info info;
    int port = 0;
    private boolean flag = false;
    int portsend = 0 ;
    InetAddress address = null;
    private int[] num = new int[100];

    Send(Info info) {
        System.out.println("send creat");
        this.info = info;
    };

    public void run() {
        try {
            while (true) {
                info = Server.callsend();
                flag = info.Flag1();
                if (flag) {
                    socket = info.Soc();
                    portsend = info.ports();
                    address = info.Address();
                    buf2 = info.Bye();
                    packet2 = new DatagramPacket(buf2, buf2.length,address,portsend);
                    System.out.println("send work");
                    socket.send(packet2);
                    num = info.Num();
                    System.out.println("+: "+ num[0]+ "times ");
                    System.out.println("-: "+ num[1]+ "times ");
                    System.out.println("*: "+ num[2]+ "times ");
                    System.out.println("/: "+ num[3]+ "times ");
                    flag = false;
                    info.flagn1(flag);
                    Server.callback(info);
                }
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}
