package main;

import org.ych.techDemo.netty.encoder.Message;
import org.ych.techDemo.netty.nettyServer.EchoServer;
import org.ych.techDemo.netty.nettyClient.EchoClient;

public class Application {
    public static void main(String[] args) {
        if (args.length > 0 && "server".equals(args[0])) {
            try {
                EchoServer.startServer(args);
            } catch (Exception e) {
                e.printStackTrace();
            }
        } else if (args.length > 0 && "client".equals(args[0])) {
            try {
                EchoClient.startClient(args);
            } catch (Exception e) {
                e.printStackTrace();
            }
        } else if (args.length > 0 && "message".equals(args[0])) {
            Message.startMessage(args);
        }
    }
}
