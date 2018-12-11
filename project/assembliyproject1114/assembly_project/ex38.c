#include<stdio.h>
#define N 15
unsigned int a;
char input[N];
char s[N];
int main()
{
	scanf("%s", input);
	_asm{
		lea edi, input
		//堆栈传递参数
		push edi
		//十进制字符串转十进制数，返回值放入eax中
		call to_value
		//平衡堆栈
		add esp, 4

		//esi为转换后的十六进制字符串首地址
		lea esi, s
		//堆栈传递参数s,a
		push esi
		push eax
		//10进制转16进制
		call to_hex
		//平衡堆栈
		add esp, 8
	}
	printf("%s\n", s);
	return 0;
	_asm{
	//子程序：十进制字符串转换为十进制数值
	//入口：堆栈传递十进制字符串首地址
	//出口：eax = 十进制数值
to_value:
		push ebp
		mov ebp, esp
		//十进制字符串首地址存放到esi中
		mov esi, [ebp+8]
		xor edx,edx
		xor eax,eax
lab1:
		imul edx, 10
		//[esi]范围为‘0’-‘9’
		mov al, [esi]
		inc esi
		//去掉al高8位，只取低8位即是要转换的十进制字符
		and al, 0fh
		//结果存放到edx中
		add edx, eax
		//转换完成则跳出循环
		cmp [esi], 0
		jnz lab1
		//准备返回值
		mov eax, edx
		pop ebp
		ret
		}
	_asm{
		//子程序：十进制数值转换为十六进制字符串
		//入口：堆栈中的参数依次为转换后的十六进制字符串首地址、十进制数值
		//出口：无
to_hex:
		push ebp
		mov ebp, esp
		//....................mov not lea...................
		//esi为转换后的十六进制字符串首地址
		mov esi, [ebp+12]
		//edi为十进制数值
		mov edi, [ebp+8]
		xor ecx, ecx
		//除数为16
		mov ebx, 16
L1:
		//edx：eax为被除数
		//被除数低32位放入eax中
		mov eax, edi
		//被除数高32位置为0
		xor edx, edx

		div ebx
		call Dxx
		//余数压入栈中
		push edx
		//计数
		inc ecx

		//商即新的低32位被除数放入edi中
		mov edi, eax
		//edi为0则停止循环
		cmp edi, 0
		jne L1
	
		//把堆栈中的所有内容取出到s中
L2:
		pop edx
		//转换后的值存入字符串中
		mov [esi], dl
		inc esi
		//ecx为0恰好存完
		loop L2
		//添加字符串结束符号
		mov [esi], 0
		pop ebp
		ret
	//子程序：十进制数值(范围为0-15)转为16进制字符
	//入口：edx = 十进制数值
	//出口：edx = 十六进制字符
Dxx:
		add edx, 30h
		cmp edx, '9'
		ja More
		ret
More:
		add edx, 7
		ret
		}
}
