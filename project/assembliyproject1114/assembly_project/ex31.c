#include<stdio.h>
char s[100];
int main()
{
	gets(s);
	_asm{
		//取字符串地址到esi寄存器中
		lea esi, s
		//设置循环变量用于遍历字符串
		mov ecx, 0
	L:
		//如果输入的是空字符串，虽然调用了conv，但是处理完后仍然不变
		//取得当前要处理的字符到al中
		mov al, byte ptr[esi+ecx]
		//调用大写转小写函数
		call conv
		//处理完后再送到原字符串相应位置
		mov byte ptr[esi+ecx], al
		inc ecx
		//判断下一个要处理的字符是否是字符串终结符号
		cmp byte ptr [esi+ecx], 0
		//如果不是的话就继续循环
		jne L 
	}
	printf("%s\n", s);
	return 0;
	_asm{
		//子程序： 把可能的大写字母转小写字母
		//入口：al = 待转换的字母
		//出口：al = 转换后的字母
conv:
		//字符串是A-Z范围则+20h， 否则不处理
		cmp al, 'A'
		jb over 
		cmp al, 'Z'
		ja over
		add al, 20h
	over:
		ret
	}
}
