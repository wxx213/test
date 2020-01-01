#
# before this, need to start zookeeper server successfully first.
#  1. $cp $(ZK_DIR)/conf/zoo_sample.cfg $(ZK_DIR)/conf/zoo.cfg
#  2. if start sevice failed because of port conflication, need to config
#     new port number in $(ZK_DIR)/conf/zoo.cfg with new line like
#         admin.serverPort=8081
#  3. cd $(ZK_DIR)/bin && ./zkServer-initialize.sh
#  4. cd $(ZK_DIR)/bin && ./zkServer.sh start
#  5. cd $(ZK_DIR)/bin && ./zkCli.cmd
#     or cd $(ZK_DIR)/bin && ./zkCli.cmd ./zkCli.sh -server localhost:2181
#
ZK_DIR=/home/wxx123/projects/storage/apache-zookeeper-3.5.6-bin
ZK_LIB_DIR=/home/wxx123/projects/storage/apache-zookeeper-3.5.6-bin/lib

all:
	javac -cp .:$(ZK_LIB_DIR)/zookeeper-3.5.6.jar:$(ZK_LIB_DIR)/zookeeper-jute-3.5.6.jar:$(ZK_LIB_DIR)/slf4j-api-1.7.25.jar -d . *.java
	java -cp .:$(ZK_LIB_DIR)/zookeeper-3.5.6.jar:$(ZK_LIB_DIR)/zookeeper-jute-3.5.6.jar:$(ZK_LIB_DIR)/slf4j-api-1.7.25.jar zktest.Main

clean:
	rm -rf zktest

