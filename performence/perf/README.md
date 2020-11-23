# install perf in Ubuntu
apt install -y linux-tools-common

# download 
git clone https://github.com/brendangregg/FlameGraph.git

# sample, 上述代码中perf record表示记录，-F 99表示每秒99次，-p 181是进程号，
# 即对哪个进程进行分析，-g表示记录调用栈，sleep 60则是持续时间
## sample cpu with 99Hz, will generate perf.data file
perf record -F 99 -a -g -- sleep 60

## sample process with pid 181, will generate perf.data file
perf record -F 99 -p 181 -g -- sleep 60

# 解决可能出现的问题：failed to open perf.data: Permission denied
perf report -n

# 生成脚本文件 
perf script -i perf.data &> perf.unfold

# 
./FlameGraph/stackcollapse-perf.pl perf.unfold &> perf.folded

# 执行完成后生成perf.svg图片，可以下载到本地，用浏览器打开perf.svg
./FlameGraph/flamegraph.pl perf.folded > perf.svg
