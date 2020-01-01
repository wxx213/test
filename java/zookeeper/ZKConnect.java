/**
 * @Date: 19-1-28
 * @version： V1.0
 * @Author: Chandler
 * @Description: ${todo}
 */
package zktest;

import java.io.*;

import org.apache.zookeeper.WatchedEvent;
import org.apache.zookeeper.Watcher;
import org.apache.zookeeper.ZooKeeper;

// @Slf4j
public class ZKConnect implements Watcher {

    public static final String zkServerPath = "127.0.0.1:2181";

    public static final Integer timeout = 5000;

    public static void ConnectTest() throws IOException, InterruptedException {
        ZooKeeper zk = new ZooKeeper(zkServerPath,timeout,new ZKConnect());
        System.out.print("客户端开始连接zookeeper服务器...\n");
        System.out.print("连接状态:"+zk.getState()+"\n");

        new Thread().sleep(2000);

        System.out.print("连接状态:"+zk.getState()+"\n");
    }

    @Override
    public void process(WatchedEvent watchedEvent) {
        System.out.print("接收到watch通知:"+watchedEvent+"\n");
    }
}
