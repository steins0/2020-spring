import java.net.*;
import java.io.*;

public class UDPServerThread extends Thread{
	DatagramSocket socket = null;
	DatagramPacket packet = null;
	byte[] data = null;

	public UDPServerThread(byte[] data,DatagramSocket socket,DatagramPacket packet) {
		this.socket = socket;
		this.packet = packet;
		this.data = data;
	}
	public void run(){
				//System.out.println("go");
				String info = new String(data);
				System.out.println(info);
				InetAddress address = packet.getAddress();
				int port = packet.getPort();
				DatagramPacket packet2 = new DatagramPacket(data, data.length, address, port);
				try {
					socket.send(packet2);
					System.out.println("server end");
				} catch (IOException e) {
					e.printStackTrace();
				}finally{
				}
	}
}