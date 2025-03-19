# 关于c的输入流
## scanf()和scanf_s()

# c的输出流
## printf()和printf_s()
printf()和printf_s()的主要区别：printf_s()中`%n`这个格式说明符（format speifier）是不合法的。  
`%n`对于的变元必须是`*int`类型，它的作用是把字符数输入stdout。  
eg:
```c
#include<stdio.h>
int main(void)
{
        int s;
        printf("12345%ns :", &s);
        printf("%d\n", s);
        return 0;
}
```
result：12345s :5  

__关于printf_s()的格式：__
|en|format specifier begin with %|flags|field_width|precision|size_flag|conversion_character|
|---|---|---|---|---|---|---|
|cn|%是格式说明符的开始标志|影响输出的标志|输出的字符宽度|精度|尺寸标记（修饰后面的格式符号）|使用的输出转换类型（格式符号）|
|content|%|(-,+,space,#or0)|number|.n(结果保留n位小数)|(h,hh,l,ll,j,z,t,L)|(d/i,o,u,x,X,f/F,e,E,g,G,A/a,p,c,s)|
|meaning||+:为有符号数添加符号<br>-：输出值在输出字段中左对齐<br>0:在输出值前面填充0至填满宽度<br>#:在八进制输出值前面加0，十六进制数前面加0x，浮点数包含小数点<br>space:在正数或者0前面加一个空格，而不是+号|用数字表示输出字段的宽度|常用于浮点数输出|h:表示short或unsigned short<br>hh:signed char或unsigned char<br>l:表示整数是long或者unsigned long<br>ll:表示整数是long long或者unsigned long long<br>L:long double|d/i:带符号的十进制整数<br>o,u,x:无符号的八，十，十六进制整数<br>X:使用大写的ABCDEF表示十六进制数，其他和x相同<br>f/F:带符号的小数<br>e/E:带符号和指数的小数<br>p:指针类型<br>c:单个字符<br>s:一个字符串|

其中可插入转义字符：（以反斜杠\开头）  
\b: 退格  
\f: 换页  
\n: 换行  
\r: 回车，移动到当前行开头  
\t: 水平制表符