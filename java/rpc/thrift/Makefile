
build: clean
	mvn package
	mvn install

server_exec:
	mvn exec:java -pl server -Dexec.mainClass="server.HelloServerDemo"

client_exec:
	mvn exec:java -pl client -Dexec.mainClass="client.HelloClientDemo"

clean:
	mvn clean
