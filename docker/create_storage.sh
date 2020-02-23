#!/bin/bash

# 创建loop设备
dd if=/dev/zero of=/root/tmp/data.img bs=1K count=1 seek=10M
dd if=/dev/zero of=/root/tmp/meta.data.img bs=1K count=1 seek=100K
losetup /dev/loop2015 /root/tmp/data.img
losetup /dev/loop2016 /root/tmp/meta.data.img

# 创建thin pool wxx-thin-pool
dmsetup create wxx-thin-pool --table "0 20971522 thin-pool /dev/loop2016 /dev/loop2015 128 65536 1 skip_block_zeroing"

# 基于thin pool “wxx-thin-pool” 创建thin volume “wxx-thin-volumn-001”并挂载，wxx-thin-volumn-001设备号为0
dmsetup message /dev/mapper/wxx-thin-pool 0 "create_thin 0"
dmsetup create wxx-thin-volumn-001 --table "0 2097152 thin /dev/mapper/wxx-thin-pool 0"
# 只能格式化设备号为0的这个thin volume “wxx-thin-volumn-001”
mkfs.ext4 /dev/mapper/wxx-thin-volumn-001

mkdir  -p /root/tmp/mnt/base
mount /dev/mapper/wxx-thin-volumn-001 /root/tmp/mnt/base
echo "hello world, I am a base" > /root/tmp/mnt/base/id.txt

# 基于wxx-thin-volumn-001做快照（冻结wxx-thin-volumn-001），创建出新的thin volume "mysnap1"设备号为1
dmsetup message /dev/mapper/wxx-thin-pool 0 "create_snap 1 0"
dmsetup create mysnap1 --table "0 2097152 thin /dev/mapper/wxx-thin-pool 1"
mkdir -p /root/tmp/mnt/mysnap1
mount /dev/mapper/mysnap1 /root/tmp/mnt/mysnap1
echo "I am snap1" >> /root/tmp/mnt/mysnap1/id.txt
echo "I am snap1" > /root/tmp/mnt/mysnap1/snap1.txt

# 基于mysnap1做快照（冻结mysnap1），创建出新的thin volume ”mysnap2“，设备号为2
dmsetup message /dev/mapper/wxx-thin-pool 0 "create_snap 2 1"
dmsetup create mysnap2 --table "0 2097152 thin /dev/mapper/wxx-thin-pool 2"
mkdir -p /root/tmp/mnt/mysnap2
mount /dev/mapper/mysnap2 /root/tmp/mnt/mysnap2
echo "I am snap2" >> /root/tmp/mnt/mysnap2/id.txt
echo "I am snap2" > /root/tmp/mnt/mysnap2/snap2.txt
