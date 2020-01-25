#!/bin/bash

NODE_NUM=$1

DISCOVERY_URL=`curl https://discovery.etcd.io/new?size=$NODE_NUM`

for((i=1;i<=$NODE_NUM;i++));
do
	docker run -itd --name ed$i --env ETCD_DISCOVERY_URL=$DISCOVERY_URL etcd
	if [ $? != 0 ]
	then
		exit 1
	fi
done
exit 0
