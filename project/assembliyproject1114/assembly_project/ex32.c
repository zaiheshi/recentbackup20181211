#include<stdio.h>
char s[100];
//a为字母数量
int a = 0;
//b为数字数量
int b = 0;
int main()
{
	//读取字符串
	scanf("%s", s);
	_asm{
		//字符串首地址放入esi中
		lea esi, s
	L:
		mov bl, byte ptr[esi]
		//分别调用lower、upper、digit计算字母与数字个数，返回值存入eax中
		xor eax, eax
		call lower 
		//字母用a统计
		add a, eax

		xor eax, eax
		call upper
		add a, eax
		
		xor eax, eax
		call digit
		//数字用b统计
		add b, eax
		
		//判断并处理下一个字符
		inc esi
		cmp  byte ptr[esi], 0
		jne L
	}
	printf("alpha %d, number %d\n", a, b);
	return 0;
	_asm{
		//子程序：统计小写字母个数
		//入口：bl = 单个字符
		//出口：eax = 小写字母个数
	lower:
			cmp bl, 'a'
			jb over 
			cmp bl, 'z'
			ja over
			inc eax
			ret
		//子程序：统计大写字母个数
		//入口：bl = 单个字符
		//出口：eax = 大写字母个数
	upper:
			cmp bl, 'A'
			jb over
			cmp bl, 'Z'
			ja over
			inc eax
			ret
		//子程序：统计数字字符个数
		//入口：bl = 单个字符
		//出口：eax = 数字字符个数
	digit:	
			cmp bl, '0'
			jb over
			cmp bl, '9'
			ja over
			inc eax
	over:
			ret
	}
	return 0;
}
