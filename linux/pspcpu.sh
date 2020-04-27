#!/bin/bash

set -e

pid=$1

Hertz=`getconf CLK_TCK`

uptime=`cat /proc/uptime | awk {'print $1'}`

utime=`cat /proc/$pid/stat | awk {'print $14'}`
stime=`cat /proc/$pid/stat | awk {'print $15'}`
cutime=`cat /proc/$pid/stat | awk {'print $16'}`
cstime=`cat /proc/$pid/stat | awk {'print $17'}`

starttime=`cat /proc/$pid/stat | awk {'print $22'}`

total_time=`expr $utime + $stime`

seconds=`echo "$uptime - $starttime / $Hertz" | bc`

pcpu=`echo "($total_time * 1000 / $Hertz) / $seconds" | bc`

echo pcpu: $pcpu

pcpu1=`expr $pcpu / 10`
pcpu2=`expr $pcpu % 10`

echo pcpu%: $pcpu1.$pcpu2%
