
all:
	javac -cp .:jedis-2.9.0.jar:commons-pool2-2.8.0.jar -d . *.java
	java -cp .:jedis-2.9.0.jar:commons-pool2-2.8.0.jar redistest.RedisTest

clean:
	rm -rf redistest
