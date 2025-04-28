#include <pthread.h>
#include <stdio.h>

static int shared_mem = 0;

int load(){
    return shared_mem;
}

void store(int value){
    shared_mem = value;
}

void T_sum() {
    for (int i = 0; i < 10; i++) {
        int t = load();
        t += 1;
        store(t);
    }
}

/*
thread1: 第三次load(1), store(shared_mem, 2)
thread2: load(0), store(shared_mem, 1)
thread3: 

thread2 执行到load(0),store(shared_mem, 1)时，thread1 执行到第三次load(1), 然后执行完线程2和线程3的全部指令，无论中间值是多少，最后thread1都是执行了store(shared_mem, 2) 
*/