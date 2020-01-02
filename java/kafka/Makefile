#
# 1. start zookeeper
#    $cd $(KAFKA_DIR)/bin && ./zookeeper-server-start.sh -daemon ../config/zookeeper.properties
# 2. start kafka
#    $cd $(KAFKA_DIR)/bin && ./kafka-server-start.sh -daemon ../config/server.properties
# 3. modify kafka listen server address
#    $cd $(KAFKA_DIR)/config && vim server.properties
#        listeners=PLAINTEXT://192.168.2.101:9092
# 4. make sure the right listen server address in codes
#

KAFKA_DIR=/home/wxx123/projects/storage/kafka_2.12-2.4.0
KAFKA_LIB_DIR=$(KAFKA_DIR)/libs

KAFKA_JARS=$(KAFKA_LIB_DIR)/kafka-clients-2.4.0.jar:$(KAFKA_LIB_DIR)/kafka_2.12-2.4.0.jar:$(KAFKA_LIB_DIR)/kafka-streams-2.4.0.jar:$(KAFKA_LIB_DIR)/slf4j-log4j12-1.7.28.jar:$(KAFKA_LIB_DIR)/slf4j-api-1.7.28.jar:$(KAFKA_LIB_DIR)/log4j-1.2.17.jar

all:
	javac -cp .:$(KAFKA_JARS) -d . *.java
	java -cp .:$(KAFKA_JARS) kafkatest.KafkaConsumerTest &
	java -cp .:$(KAFKA_JARS) kafkatest.KafkaProducerTest &

clean:
	rm -rf kafkatest

