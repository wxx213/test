
#
# go get go.etcd.io/etcd/clientv3
# or put https://github.com/etcd-io/etcd/tree/master/clientv3 into go source
#
all:
	go build
	./etcd

docker_image:
	docker build -t etcd .

clean:
	rm etcd
