
#
# go get go.etcd.io/etcd/clientv3
# or put https://github.com/etcd-io/etcd/tree/master/clientv3 into go source
#

ETCD_NODES = 3

all:
	go build
	./etcd

docker_image:
	docker build -t etcd .

etcd_cluster:
	./deploy_etcd_cluster.sh $(ETCD_NODES) etcd

etcd_cluster_dns:
	./deploy_etcd_cluster.sh $(ETCD_NODES) dns

clean:
	rm etcd
