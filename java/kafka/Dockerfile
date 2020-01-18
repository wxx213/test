FROM centos:7

RUN yum install -y wget net-tools
RUN yum install -y java-1.8.0-openjdk

RUN mkdir -p /usr/local/kafka
RUN wget http://mirrors.tuna.tsinghua.edu.cn/apache/kafka/2.4.0/kafka_2.12-2.4.0.tgz
RUN tar -xzvf kafka_2.12-2.4.0.tgz -C /usr/local/kafka/
RUN rm kafka_2.12-2.4.0.tgz

COPY kafka.sh /usr/local/bin/kafka.sh
CMD /bin/bash /usr/local/bin/kafka.sh
