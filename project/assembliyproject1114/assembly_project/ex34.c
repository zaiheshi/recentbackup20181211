#include<stdio.h>
int a, b;
char buff1[20], buff2[20];
int summ, difff, mull;
int main()
{
	//读取第一个自然数存入buff1中
	scanf("%s", buff1);
	//读取第二个自然数存入buff2中
	scanf("%s", buff2);
	_asm {
		//第一个自然数首地址放入esi中
		lea esi, buff1
		//调用子程序实现十进制字符串转十进制数
		call strtovalue
		//返回值放入a中
		mov a, eax
		//第二个自然数首地址放入esi中
		lea esi, buff2
		//调用子程序实现十进制字符串转十进制数
		call strtovalue
		//返回值放入b中
		mov b, eax
		push a
		push b
		//求两数之和
		call SUM
		//返回值放入summ中
		mov summ, eax
		//平衡堆栈
		add esp, 8
	}
	printf("sum is %d\n", summ);

	_asm {
		push b
		push a
		//求两数之差
		call DIFF
		//返回值放入difff中
		mov difff, eax
		//平衡堆栈
		add esp, 8
	}
	printf("diff is %d\n", difff);
	_asm {
		push b
		push a
		//求两数之积
		call MULTI
		//返回值放入mull中
		mov mull, eax
		//平衡堆栈
		add esp, 8
	}
	printf("mul is %d\n", mull);
	return 0;
	_asm {
		//子程序：十进制字符串转换为十进制数、
		//入口：esi = 字符串首地址
		//出口：eax = 转换后的十进制数
strtovalue:
		xor edx, edx
		xor eax, eax
	LAB1:
		mov al, [esi]
		//处理到字符串结尾则跳转到LAB2
		cmp al, 0
		je LAB2
		inc esi
		//获取字符的十进制值
		and al, 0FH
		//Y*10
		imul edx, 10
		//Y*10+al
		add edx, eax
		//循环
		jmp LAB1
	LAB2:
		//准备返回值
		mov eax, edx
		ret

		//子程序: 求两数之和
		//入口：堆栈push 32位的两个数
		//出口：eax = 两数之和
	SUM :
		push ebp
		mov ebp, esp
		mov eax, [ebp + 8]
		mov ebx, [ebp + 12]
		add eax, ebx
		mov esp, ebp
		pop ebp
		ret
		//子程序: 求两数之差
		//入口：堆栈push 32位的两个数
		//出口：eax = 两数之差
	DIFF :
		push ebp
		mov ebp, esp
		mov eax, [ebp + 8]
		mov ebx, [ebp + 12]
		sub eax, ebx
		mov esp, ebp
		pop ebp
		ret
		//子程序: 求两数之积
		//入口：堆栈push 32位的两个数
		//出口：eax = 两数之积
	MULTI :
		push ebp
		mov ebp, esp
		mov eax, [ebp + 8]
		mov ebx, [ebp + 12]
		mul ebx
		//此处结果只取低32位
		mov esp, ebp
		pop ebp
		ret
	}
}
