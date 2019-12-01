package process;

import process.TestThread;
import process.TestRunnable;
import process.TestSleep;
import process.TestJoin;
import process.TestYield;
import process.TestCallable;

public class Main {
	public static void main(String arg[]){
		System.out.print("Hello Java!\n");
		TestThread.testthread();
		TestRunnable.testrunnable();
		TestSleep.testsleep();
		try {
			TestJoin.testjoin();
		} catch (InterruptedException e) {

		} finally {

		}
		TestYield.testyield();
		TestCallable.testcallable();
	}
}

