import java.io.*;
import java.net.*;
import java.util.concurrent.ArrayBlockingQueue;
import java.util.concurrent.ThreadPoolExecutor;
import java.util.concurrent.TimeUnit;

public class EchoServer {
	public static void main(String[] args) throws Exception {
		Socket clientSocket = null;
		ServerSocket listenSocket = new ServerSocket(8189);

		for (int i = 0; i < 15; i++) {
			ThreadPoolExecutor executor = new ThreadPoolExecutor(5, 10, 200, TimeUnit.MILLISECONDS,
				new ArrayBlockingQueue<Runnable>(5));
			
			while(true){
				try {
					System.out.println("Server listening at 8189");
					clientSocket = listenSocket.accept();
					TCPserverpool mytcp = new TCPserverpool(clientSocket, i);
					executor.execute(mytcp);
					System.out.println("Accepted connection from client");
				} catch (IOException e) {
					e.printStackTrace();}
			}
		}
		clientSocket.close();
		listenSocket.close();
	}
}