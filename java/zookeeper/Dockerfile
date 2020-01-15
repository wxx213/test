FROM centos:7

RUN yum install -y wget net-tools
RUN yum install -y java-1.8.0-openjdk

RUN mkdir -p /usr/local/zookeeper
RUN wget https://mirrors.tuna.tsinghua.edu.cn/apache/zookeeper/zookeeper-3.5.6/apache-zookeeper-3.5.6-bin.tar.gz
RUN tar -xzvf apache-zookeeper-3.5.6-bin.tar.gz -C /usr/local/zookeeper/
RUN rm apache-zookeeper-3.5.6-bin.tar.gz

