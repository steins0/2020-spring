import java.io.*;
import java.net.Socket;

public class TCPserverpool implements Runnable {
    private int tasknum;
    Socket socket = null;

    public TCPserverpool(Socket socket, int num) {
        this.socket = socket;
        this.tasknum = num;
    }

    public void run() {
        try {
            InputStream inStream = socket.getInputStream();
            OutputStream outStream = socket.getOutputStream();
            BufferedReader in = new BufferedReader(new InputStreamReader(inStream));
            PrintWriter out = new PrintWriter(outStream);

            String line = null;
            while ((line = in.readLine()) != null) {
                System.out.println("Message from client:" + line);
                out.println(line);
                out.flush();
            }
            in.close();
            out.close();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}
