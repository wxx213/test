#!/bin/bash

/usr/local/kafka/kafka_2.12-2.4.0/bin/zookeeper-server-start.sh -daemon /usr/local/kafka/kafka_2.12-2.4.0/config/zookeeper.properties
/bin/sleep 1
/usr/local/kafka/kafka_2.12-2.4.0/bin/kafka-server-start.sh -daemon /usr/local/kafka/kafka_2.12-2.4.0/config/server.properties
/bin/bash
