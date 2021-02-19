package main;

import zktest.ZKClusterNodeOperator;
import zktest.ZKConnect;
import zktest.ZKConnectSessionWatcher;
import zktest.ZKNodeOperator;

import java.io.*;

public class Application {
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

