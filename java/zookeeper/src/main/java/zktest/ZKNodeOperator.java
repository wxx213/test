/**
 * @Date: 19-1-28
 * @version： V1.0
 * @Author: Chandler
 * @Description: ${todo}
 */
package zktest;

import java.io.*;
import java.util.*;

import org.apache.zookeeper.WatchedEvent;
import org.apache.zookeeper.Watcher;
import org.apache.zookeeper.ZooKeeper;
import org.apache.zookeeper.data.ACL;
import org.apache.zookeeper.CreateMode;
import org.apache.zookeeper.ZooDefs.Ids;
import org.apache.zookeeper.KeeperException;
import org.apache.zookeeper.data.Stat;

public class ZKNodeOperator implements Watcher {

    private ZooKeeper zooKeeper = null;
	private static int ver;

    public static final String zkServerPath = "127.0.0.1:2181";
    public static final Integer timeout = 5000;

    public ZKNodeOperator() {
    }

    public ZKNodeOperator(String connectingString){
        try {
            zooKeeper = new ZooKeeper(connectingString,timeout,new ZKNodeOperator());
        } catch (IOException e){
            e.printStackTrace();
            if (zooKeeper != null) {
                try {
                    zooKeeper.close();
                } catch (InterruptedException e1){
                    e1.printStackTrace();
                }
            }
        }
    }

    /**
     * 创建zk结点
     */
    public void createZKNode(String path, byte[] data, List<ACL> acls){
        String result = "";
        try {
            result = zooKeeper.create(path,data,acls, CreateMode.PERSISTENT);
            System.out.println("创建节点：\t" + result + "\t成功...");
            new Thread().sleep(2000);
        } catch (Exception e){
            e.printStackTrace();
        }
    }

    public static void NodeOperatorTest() {
        ZKNodeOperator zkServer = new ZKNodeOperator(zkServerPath);

        zkServer.createZKNode("/testnode", "testnode".getBytes(), Ids.OPEN_ACL_UNSAFE);

		try {
			Stat status  = zkServer.zooKeeper.setData("/testnode", "xyz".getBytes(), 0);
			ver = status.getVersion();
			System.out.println("当前版本"+ver);
		} catch (InterruptedException ite) {

		}  catch (KeeperException ke) {

		}
		try {
			Thread.sleep(2000);
		} catch (InterruptedException ite) {
			
		}

		Stat stat = new Stat();
		try {
        	byte[] resByte = zkServer.zooKeeper.getData("/testnode", true, stat);
        	String result = new String(resByte);
        	System.out.println("当前值:" + result);
		} catch (KeeperException ke) {

		} catch (InterruptedException ite) {

		}

		try {
			zkServer.zooKeeper.delete("/testnode", ver);
			System.out.println("删除节点成功");
		} catch (InterruptedException ite) {

		} catch (KeeperException ke) {

		}

		try {
			Thread.sleep(2000);
		} catch (InterruptedException ite) {

		}
    }

    @Override
    public void process(WatchedEvent event) {

    }
}
