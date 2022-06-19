#FROM openanolis/anolisos:7.9-x86_64
FROM centos:7

RUN mkdir -p /var/dockervm

COPY ./linux.img /var/dockervm/linux.img

COPY ./qemu-ifdown /var/dockervm/qemu-ifdown
COPY ./qemu-ifup /var/dockervm/qemu-ifup
COPY ./start_qemu.sh /var/dockervm/start_qemu.sh

RUN yum install -y qemu-kvm tc iproute socat
