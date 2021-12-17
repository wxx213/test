#include <poll.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/eventfd.h>
#include <pthread.h>

int efd;

void *run_eventfd_write(void *arg) {
    uint64_t count = 1;
    while (1) {
        printf("write count: %zu\n", count);
        write(efd, &count, sizeof(count));
        count++;
        sleep(2);
    }
}

int main() {
    struct pollfd fds;
    pthread_t pid;

    unsigned int initval = 1000;  // 观察将 1000 改为 0 后打印的顺序
    int flags = 0;
    int timeout = 1000;

//     flags |= EFD_SEMAPHORE; // 观察将该注释取消打印的结果
    efd = eventfd(initval, flags);
    fds.fd = efd;
    fds.events |= POLLIN;

    pthread_create(&pid, NULL, run_eventfd_write, NULL);

    while (1) {
        int ret = poll(&fds, 1, timeout);
        if (ret > 0) {
            uint64_t count;
            read(efd, &count, sizeof(count));
            printf("read count: %zu\n", count);
        }
    }
}
