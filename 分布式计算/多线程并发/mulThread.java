import java.net.*;
import java.io.*;
import java.util.concurrent.LinkedBlockingQueue;
import java.util.concurrent.BlockingQueue;
import java.util.regex.*; //正则表达式的包

public class mulThread {
    private static final int port = 677;
    private DatagramSocket socket; // 初始化服务器端口
    byte[] buf1 = new byte[1000]; // 接受数据
    byte[] buf2 = new byte[1000]; // 返回数据
    DatagramPacket packet = new DatagramPacket(buf1, buf1.length); // 接受packet
    DatagramPacket packet2 = new DatagramPacket(buf2, buf2.length); // 返回packet
    BlockingQueue<String> blockingQueue = new LinkedBlockingQueue(5); // 计算线程的队列，最大队列为5

    int[] num = new int[4]; // 对计算进行计数，依次+、-、*、/

    class Received extends Thread // 接受主线程
    {

        Received() {
            try {
                socket = new DatagramSocket(port);
            } catch (SocketException e) {
                e.printStackTrace();
            }
        };

        public void run() {
            try {
                socket.receive(packet);
            } catch (IOException e) {
                e.printStackTrace();
            }
        }
    }

    class March extends Thread // 计算主线程，我的输入样例是：1+2
    {
        public void run() {
            String info = new String(buf1);
            try {
                blockingQueue.put(info);
            } catch (InterruptedException e) {
                e.printStackTrace();
            } // 加入队列
            int num1, num2, ans = 0;
            String st1 = "(.*)(\\-)(.*)"; // 检测-号之前与减号之后，.*表示任意值，\\-表示-的转义符
            String st2 = "(.*)(\\+)(.*)";
            String st3 = "(.*)(\\*)(.*)";
            String st4 = "(.*)(\\/)(.*)";
            Pattern p = Pattern.compile(info); // 正则表达中存储的原信息
            Matcher m1 = p.matcher(st1); // 正则表达的匹配函数
            Matcher m2 = p.matcher(st2);
            Matcher m3 = p.matcher(st3);
            Matcher m4 = p.matcher(st4);
            if (m1.find()) {
                num1 = Integer.valueOf(m1.group(1)).intValue(); // groud返回三个值，对应检测的三个括号内的数，
                num2 = Integer.valueOf(m1.group(3)).intValue();
                ans = num1 - num2;
                num[1]++;
            }
            if (m2.find()) {
                num1 = Integer.valueOf(m2.group(1)).intValue();
                num2 = Integer.valueOf(m2.group(3)).intValue();
                ans = num1 + num2;
                num[0]++;
            }
            if (m3.find()) {
                num1 = Integer.valueOf(m3.group(1)).intValue();
                num2 = Integer.valueOf(m3.group(3)).intValue();
                ans = num1 * num2;
                num[2]++;
            }
            if (m4.find()) {
                num1 = Integer.valueOf(m4.group(1)).intValue();
                num2 = Integer.valueOf(m4.group(3)).intValue();
                ans = num1 / num2;
                num[3]++;
            }
            String send = "anwser:" + String.valueOf(ans);
            packet2.setData(send.getBytes());
            try {
                blockingQueue.take();
            } catch (InterruptedException e) {
                e.printStackTrace();
            } // 清楚队列
        }
    }

    class Send extends Thread {
        Send() {
        };

        public void run() {
            try {
                socket.send(packet2);
                System.out.println("server end");
            } catch (IOException e) {
                e.printStackTrace();
            }
        }
    }
 
}