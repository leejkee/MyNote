# 关于算法效率
- 测试程序运行的时间，使用clock()函数的返回值进行计算
```c
#include <stdio.h>
#include <time.h>

clock_t start, stop;// clock()函数返回值的类型

double duration;// 记录被测函数的运行时间，单位是秒

int main()
{
    start = clock();
    /* code */
    stop = clock();
    duration = (double)(stop - start) / CLK_TCK;
    return 0;
}
```

