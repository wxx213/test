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
public class ZKConnectSessionWatcher implements Watcher {

    public static final String zkServerPath = "127.0.0.1:2181";
    public static final Integer timeout = 5000;

    public static void SessionWatcherTest() throws Exception {

        ZooKeeper zk = new ZooKeeper(zkServerPath, timeout, new ZKConnectSessionWatcher());

        long sessionId = zk.getSessionId();
        String ssid = "0x" + Long.toHexString(sessionId);
        System.out.println(ssid);
        byte[] sessionPassword = zk.getSessionPasswd();

        System.out.print("客户端开始连接zookeeper服务器...\n");
        System.out.print("连接状态：{}"+zk.getState()+"\n");
        new Thread().sleep(1000);
        System.out.print("连接状态：{}"+zk.getState()+"\n");

        new Thread().sleep(200);

        // 开始会话重连
        System.out.print("开始会话重连...\n");

        ZooKeeper zkSession = new ZooKeeper(zkServerPath,
                timeout,
                new ZKConnectSessionWatcher(),
                sessionId,
                sessionPassword);
        System.out.print("重新连接状态zkSession：{}"+zkSession.getState()+"\n");
        new Thread().sleep(1000);
        System.out.print("重新连接状态zkSession：{}"+zkSession.getState()+"\n");
    }

    @Override
    public void process(WatchedEvent watchedEvent) {
        System.out.print("接受到watch通知：{}"+watchedEvent+"\n");
    }
}
