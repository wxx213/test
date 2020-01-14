package zktest;

import java.io.*;

public class Main {
	public static void main(String arg[]){
		System.out.print("Hello Java!\n");
		try {
			ZKConnect.ConnectTest();
		} catch (IOException ioe) {

		} catch (InterruptedException ite) {
		
		}

		try {
			ZKConnectSessionWatcher.SessionWatcherTest();
		} catch (Exception e) {

		}

		ZKNodeOperator.NodeOperatorTest();
		ZKClusterNodeOperator.ClusterNodeOperatorTest();
	}
}

