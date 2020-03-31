import java.net.*;
import java.io.*;


public class UDPServer{
	
	public static void main(String args[]){
		DatagramSocket aSocket = null;
		int serverPort = 677;
		int i = 0;
		try{
			aSocket = new DatagramSocket(serverPort);
			byte[] buffer = new byte[1000];
			while(true){
				DatagramPacket request = new DatagramPacket(buffer, buffer.length);
				aSocket.receive(request);
				UDPServerThread thread = new UDPServerThread(buffer,aSocket, request);
				thread.start();
				i++;
				System.out.println("the "+ i +"times 17030140076 LMY");
				/**
				DatagramPacket reply = new DatagramPacket(request.getData(),
				request.getLength(), request.getAddress(), request.getPort());
				aSocket.send(reply);
				**/
			}
		} catch (SocketException e){
			System.out.println("Socket: " + e.getMessage());
		} catch (IOException e) {
			System.out.println("IO: " + e.getMessage());
		} finally {
			if (aSocket != null) aSocket.close();
		}
	}
	
}

