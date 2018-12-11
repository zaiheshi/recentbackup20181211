#include<stdio.h>
#define N 100
char c;
char s[N];
int main()
{
	//读取字符到c中
	scanf("%c", &c);
	_asm{
		//转换后的二进制字符串首地址
		lea esi, s
		xor ax, ax
		//输入字符放到al中
		mov al, c	
		//to_ascII实现把字符转换为ascII码二进制值，返回值存放在esi中，采用寄存器(esi， al)传递参数
		call to_ascII
	}
	printf("转换后的二进制值%s\n", s);
	return 0;
	_asm{
		//子程序：单个字符转换为对应的ascii码的二进制字符串
		//入口：al = 字符，esi = 转换后的二进制字符串首地址
		//出口：无
to_ascII:
		//总共循环8次
		mov ecx, 8
L:
		//循环左移1位
		rol al, 1
		mov bl, al
		//取最后一位与01h做与操作得出当前位的数字
		and bl, 01h
		//转为对应的数字字符'0' or '1'
		add bl, 30h
		//存入s中
		mov [esi], bl
		inc esi
		loop L
		//添加字符串结束标志
		mov [esi], 0
		ret
}
}
