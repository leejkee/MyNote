# 最大子列和
- 算法1
暴力计算全部子列和
T(N) = O(N^3)
```c
int MaxSumseqSum(int A[], int N)
{
    

}
```
- 算法2
使用前一次加和加上下一个元素来计算下一个子列的和
T(N) = O(N^2)

```c
int MaxSubseqSum(int A[], int N)
{
    int ThisSum, MaxSum = 0;
    int i, j;
    for (i = 0; i < N; ++i)
    {
        ThisSum = 0;
        for (j = i; j < N; ++j)
        {
            ThisSum += A[j];// 加一次和MaxSum比较一次，如果更大就更新MaxSum的值
            if (THisSum > MaxSum)
            {
                MaxSum = ThisSum;
            }
        }
    }
    return MaxSum;
}
```
- 算法3
分而治之

— 算法4
在线处理
抛弃以负子列和开始的处理，因为负的值只能让后面的子列和减小
```c
#include <stdio.h>
int main()
{
    return 0;
}
```
