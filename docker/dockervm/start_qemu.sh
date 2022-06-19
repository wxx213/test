#!/bin/bash

while [ 1 ]; do
	if [ -f "/run/dockervm_net.done" ]; then
		break
	fi
	sleep 1
done

$QEMU $QEMU_OPT
