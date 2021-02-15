
all:
	javac *.java -d .
	java socketserver.Server &
	java socketclient.Client

clean:
	rm -rf socketserver socketclient
	rm *.class
