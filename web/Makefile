
tomcat_image:
	docker build -t tomcat -f Dockerfile.tomcat .

dnsmasq_image:
	docker build -t dnsmasq -f Dockerfile.dnsmasq

consul_image:
	docker build -t consul -f Dockerfile.consul .

consul_cluster:
	docker run -itd --name c1 --env CONSUL_RUN_MODE=server consul
	docker run -itd --name c2 --env CONSUL_RUN_MODE=server consul
	docker run -itd --name c3 --env CONSUL_RUN_MODE=server consul
	docker run -itd --name c4 --env CONSUL_RUN_MODE=client consul
