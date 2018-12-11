#include<stdio.h>
#define N 15
unsigned int a;
char s[N];
int main()
{
	//获取输入的十进制数值
	scanf("%d", &a);
	_asm{
		//esi为转换后的十六进制字符串首地址
		lea esi, s
		xor eax,eax
		mov eax, a
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
		mov esp, ebp
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
