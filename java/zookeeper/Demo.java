package zktest;

import java.util.*;

public class Demo {
 
	public static void main(String[] args) throws Exception {
		BaseZookeeper zookeeper = new BaseZookeeper();
		System.out.println("connect zookeeper start");
		zookeeper.connectZookeeper("127.0.0.1:2181");
		System.out.println("connect zookeeper end");
		List<String> children = zookeeper.getChildren("/");
		System.out.println(children);
	}
}

