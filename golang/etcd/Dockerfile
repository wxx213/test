FROM centos:7

RUN yum install -y vim net-tools
RUN mkdir -p mkdir -p /usr/local/etcd
COPY etcd-v3.4.2-linux-amd64.tar.gz etcd-v3.4.2-linux-amd64.tar.gz
RUN tar -xzvf etcd-v3.4.2-linux-amd64.tar.gz -C /usr/local/etcd
RUN rm -f etcd-v3.4.2-linux-amd64.tar.gz
COPY etcd.sh /usr/local/bin/etcd.sh
CMD /bin/bash /usr/local/bin/etcd.sh
