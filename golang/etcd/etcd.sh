#!/bin/bash

#
# get the discovery url by:
# curl https://discovery.etcd.io/new?size=3
# https://discovery.etcd.io/dbc474e91817301dfafc4d7876a926c1
#

HOST_IP=`/sbin/ifconfig eth0 | awk '/inet/ {print $2}' | cut -f2 -d ":" |awk 'NR==1 {print $1}'`
ETCD_NAME="etcd_${HOST_IP}_ip"
DISCOVERY_URL=$ETCD_DISCOVERY_URL

/usr/local/etcd/etcd-v3.4.2-linux-amd64/etcd --name ${ETCD_NAME} --initial-advertise-peer-urls http://${HOST_IP}:2380 \
--listen-peer-urls http://${HOST_IP}:2380 \
--listen-client-urls http://${HOST_IP}:2379,http://127.0.0.1:2379 \
--advertise-client-urls http://${HOST_IP}:2379 \
--discovery $DISCOVERY_URL &

/bin/bash
