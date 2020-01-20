FROM centos:7

RUN yum install -y wget net-tools make gcc vim
RUN mkdir -p /usr/local/redis

RUN wget https://github.com/antirez/redis/archive/5.0.7.tar.gz
RUN tar -xzvf 5.0.7.tar.gz -C /usr/local/redis/
RUN rm 5.0.7.tar.gz
RUN make -C /usr/local/redis/redis-5.0.7 MALLOC=libc

COPY redis.sh /usr/local/bin/redis.sh
COPY redis_cluster.conf /usr/local/redis/redis-5.0.7/redis_cluster.conf
CMD /bin/bash /usr/local/bin/redis.sh
