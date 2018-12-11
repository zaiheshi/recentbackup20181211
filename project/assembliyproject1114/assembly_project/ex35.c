#include<stdio.h>
//写的过于繁琐了
#define N 100
//s存储输入值
char s[N];
//a为字母数量
char a[N];
//b为数字数量
char b[N];
int main()
{
	scanf("%s",s);
	_asm {
		lea esi, s
		//计算字母数量
		call alphaN
		lea esi, a
		//十进制数值转字符串
		call valtostr
		
		lea esi, s
		//计算数字数量
		call digitN
		lea esi, b
		//十进制数值转字符串
		call valtostr
	}
	printf("字母有 %s个, 数字字符有 %s个\n", a, b);
	return 0;
	_asm {
		//子程序：十进制数值转为十进制字符串
		//入口： eax = 带转换的十进制数值 esi = 十进制字符串首地址
		//出口：无
valtostr:
		mov ebx, 10
		//高32位为edx置为0 ，低32位为eax即待转换的十进制值
		xor edx, edx
		//计数
		xor ecx, ecx
	LAB3 :
		idiv ebx	//商在eax中，余数在edx中
		//每次所得为余数，最终需要逆序输出
		push edx
		//余数清0作为新的被除数高32位
		xor edx, edx
		//计数
		inc ecx
		//循环终止条件
		cmp eax, 0
		jne LAB3
	Lp:
		//通过堆栈逆序
		pop edx
		//0==>'0',其余类推
		add edx, 30H
		mov [esi], dl
		inc esi
		loop Lp
		//添加结束字符
		mov [esi], 0
		ret
	}
	_asm {
		//子程序：统计字符串中字母数量
		//入口：esi = 字符串首地址
		//出口：eax = 字母数量
alphaN:
		xor edx, edx
	LAB:
		//输入无法为空字符，所以第一个字符不可能为结束符
		mov bl, byte ptr[esi]
		call lower
		add edx, eax
		call upper
		add edx, eax
		inc esi
		//读到字符串结束标志则退出循环
		cmp  byte ptr[esi], 0
		jne LAB
		//准备返回值
		mov eax,edx
		ret
		//子程序：统计字符串中数字数量
		//入口：esi = 字符串首地址
		//出口：eax = 数字数量
digitN:
		xor edx, edx
	LAB2:
		//空字符串不会影响最终结果
		mov bl, byte ptr[esi]
		call digit
		add edx,eax
		inc esi
		//读到字符串结束标志则退出循环
		cmp  byte ptr[esi], 0
		jne LAB2
		//准备返回值
		mov eax, edx
		ret
		//子程序：判断是否为小写字母
		//入口：bl = 单个字符
		//出口：eax = 1(是)/0(否)
lower:
		xor eax, eax
		cmp bl, 'a'
		jb over
		cmp bl, 'z'
		ja over
		inc eax
		ret
		//子程序：判断是否为大写字母
		//入口：bl = 单个字符
		//出口：eax = 1(是)/0(否)
upper:
		xor eax, eax
		cmp bl, 'A'
		jb over
		cmp bl, 'Z'
		ja over
		inc eax
		ret
		//子程序：判断是否为数字字符
		//入口：bl = 单个字符
		//出口：eax = 1(是)/0(否)
digit:
		xor eax, eax
		cmp bl, '0'
		jb over
		cmp bl, '9'
		ja over
		inc eax
	over:
		ret
	}
}

