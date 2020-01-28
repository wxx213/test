#!/bin/bash

NODE_NUM=$1
DISCOVERY_TYPE=$2

if [ $DISCOVERY_TYPE == "etcd" ]
then
	DISCOVERY_URL=`curl https://discovery.etcd.io/new?size=$NODE_NUM`

	for((i=1;i<=$NODE_NUM;i++));
	do
		docker run -itd --name ed$i --env ETCD_DISCOVERY_TYPE=etcd --env ETCD_DISCOVERY_URL=$DISCOVERY_URL etcd
		if [ $? != 0 ]
		then
			exit 1
		fi
	done
elif [ $DISCOVERY_TYPE == "dns" ]
then
	DISCOVERY_SRV="example.com"

	for((i=1;i<=$NODE_NUM;i++));
	do
		docker run -itd --name ed$i --env ETCD_DISCOVERY_TYPE=dns --env WXX_ETCD_DISCOVERY_SRV=$DISCOVERY_SRV etcd
		if [ $? != 0 ]
		then
			exit 1
		fi
	done
fi
exit 0
