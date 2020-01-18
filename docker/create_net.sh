#!/bin/sh

#
# config network for docker conntainer with --net=none option
# reference: https://github.com/jpetazzo/pipework
#
GUESTNAME=$1
IFNAME=br0
CONTAINER_IFNAME=eth1
IPADDR=192.168.2.120
GATEWAY=192.168.2.1
FAMILY_FLAG="-4"


DOCKERPID=$(docker inspect --format='{{ .State.Pid }}' "$GUESTNAME")
DOCKERCID=$(docker inspect --format='{{ .ID }}' "$GUESTNAME")
DOCKERCNAME=$(docker inspect --format='{{ .Name }}' "$GUESTNAME")
NSPID=$DOCKERPID

LOCAL_IFNAME="v${CONTAINER_IFNAME}pl${NSPID}"
GUEST_IFNAME="v${CONTAINER_IFNAME}pg${NSPID}"
MTU=$(ip link show "$IFNAME" | awk '{print $5}')

#
mkdir -p /var/run/netns
rm -f "/var/run/netns/$NSPID"
ln -s "/proc/$NSPID/ns/net" "/var/run/netns/$NSPID"

# create veth-pair
ip link add name "$LOCAL_IFNAME" mtu "$MTU" type veth peer name "$GUEST_IFNAME" mtu "$MTU"
ip link set "$LOCAL_IFNAME" master "$IFNAME" > /dev/null 2>&1
ip link set "$LOCAL_IFNAME" up

# set veth-pair with container namespace
ip link set "$GUEST_IFNAME" netns "$NSPID"
ip netns exec "$NSPID" ip link set "$GUEST_IFNAME" name "$CONTAINER_IFNAME"

# set ip address
ip netns exec "$NSPID" ip "$FAMILY_FLAG" addr add "$IPADDR" dev "$CONTAINER_IFNAME"
ip netns exec "$NSPID" ip "$FAMILY_FLAG" route delete default >/dev/null 2>&1 && true
ip netns exec "$NSPID" ip "$FAMILY_FLAG" link set "$CONTAINER_IFNAME" up
ip netns exec "$NSPID" ip "$FAMILY_FLAG" route get "$GATEWAY" >/dev/null 2>&1 || \
ip netns exec "$NSPID" ip "$FAMILY_FLAG" route add "$GATEWAY/32" dev "$CONTAINER_IFNAME"
ip netns exec "$NSPID" ip "$FAMILY_FLAG" route replace default via "$GATEWAY" dev "$CONTAINER_IFNAME"

# arp setting
if installed arping; then
	IPADDR=$(echo "$IPADDR" | cut -d/ -f1)
	ip netns exec "$NSPID" arping -c 1 -A -I "$CONTAINER_IFNAME" "$IPADDR" > /dev/null 2>&1 || true
else
	echo "Warning: arping not found; interface may not be immediately reachable"
fi

# Remove NSPID to avoid `ip netns` catch it.
rm -f "/var/run/netns/$NSPID"
