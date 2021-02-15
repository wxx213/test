package socketserver;

import java.io.*;
import java.net.ServerSocket;
import java.net.Socket;

/**
 * 服务端
 */
public class Server {
    public static void main(String[] args) {
        try {
            ServerSocket serverSocket = new ServerSocket(1115);
            System.out.println("服务器启动完成...监听中");
            //开启监听，等待客户端的访问
            Socket socket = serverSocket.accept();
            //获取输入流，因为是客户端向服务端发送了数据
            InputStream inputStream = socket.getInputStream();
            //创建一个缓冲流
            BufferedReader br = new BufferedReader(new InputStreamReader(inputStream));
            String info = null;
            while ((info = br.readLine()) != null) {
                System.out.println("这里是服务端 客户端是：" + info);
            }
            //向客户端做出相应
            OutputStream outputStream = socket.getOutputStream();
            info = "这里是服务端我们接受到了你消息";
            outputStream.write(info.getBytes());
            outputStream.close();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}
