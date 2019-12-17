
all:
	javac -cp .:/etc/zookeeper/conf:/usr/share/java/log4j-1.2.jar:/usr/share/java/slf4j-api.jar:/usr/share/java/slf4j-log4j12.jar:/usr/share/java/zookeeper.jar -d . *.java
	java -cp .:/etc/zookeeper/conf:/usr/share/java/log4j-1.2.jar:/usr/share/java/slf4j-api.jar:/usr/share/java/slf4j-log4j12.jar:/usr/share/java/zookeeper.jar zktest.Demo

clean:
	rm -rf zktest

