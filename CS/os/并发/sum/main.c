#include <stdio.h>
#include <pthread.h>
#include <stdatomic.h>
#include <unistd.h> // For usleep

// 共享内存变量
static volatile int shared_mem = 0;

// 增加循环次数以增加竞争机会
#define NUM_ITERATIONS 100000 // 将每次线程的累加次数从 3 增加到 10万

// 执行累加的线程函数
void* T_sum(void* arg) {
    for (int i = 0; i < NUM_ITERATIONS; i++) {
        // 使用原子操作读取共享内存的值
        int t = __atomic_load_n(&shared_mem, __ATOMIC_SEQ_CST);

        // 对值加 1 (在线程的局部变量中进行)
        t += 1;

        // !!! 引入一个微小的延迟 !!!
        // 这个延迟大大增加了其他线程在当前线程读和写之间运行并修改 shared_mem 的概率
        // 这能更频繁地暴露读-改-写竞争条件
        usleep(1); // 休眠 1 微秒

        // 使用原子操作写入共享内存的值
        __atomic_store_n(&shared_mem, t, __ATOMIC_SEQ_CST);
    }
    return NULL;
}

int main() {
    pthread_t thread1, thread2, thread3;
    int num_threads = 3;
    long long expected_total = (long long)num_threads * NUM_ITERATIONS; // 使用 long long 防止溢出

    printf("Starting shared_mem = %d\n", shared_mem);
    printf("Expected total increments: %lld\n", expected_total);

    // 创建三个线程
    if (pthread_create(&thread1, NULL, T_sum, NULL) != 0) {
        perror("Error creating thread 1");
        return 1;
    }
    if (pthread_create(&thread2, NULL, T_sum, NULL) != 0) {
        perror("Error creating thread 2");
        return 1;
    }
    if (pthread_create(&thread3, NULL, T_sum, NULL) != 0) {
        perror("Error creating thread 3");
        return 1;
    }

    // 等待所有线程完成
    if (pthread_join(thread1, NULL) != 0) {
        perror("Error joining thread 1");
        return 1;
    }
    if (pthread_join(thread2, NULL) != 0) {
        perror("Error joining thread 2");
        return 1;
    }
    if (pthread_join(thread3, NULL) != 0) {
        perror("Error joining thread 3");
        return 1;
    }

    // 打印最终结果
    // 由于并发竞争和增量丢失，结果几乎肯定会小于期望的总数
    printf("Final shared_mem = %d\n", shared_mem);

    return 0;
}