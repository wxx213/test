package socketclient;

import java.io.*;
import java.net.Socket;

/**
 * 客户端
 */
public class Client {
    public static void main(String[] args) {
        try {
            //IP地址
            Socket socket = new Socket("localhost",1115);
            OutputStream outputStream = socket.getOutputStream();
            String info ="你好";
            //输出！
            outputStream.write(info.getBytes());
            socket.shutdownOutput();
            //接受服务器的响应
            InputStream inputStream = socket.getInputStream();
            BufferedReader br = new BufferedReader(new InputStreamReader(inputStream));
            while((info =br.readLine())!=null){
                System.out.println("接收到了服务器的响应:"+info);
            }
            outputStream.flush();
            outputStream.close();
            inputStream.close();
            socket.close();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}
