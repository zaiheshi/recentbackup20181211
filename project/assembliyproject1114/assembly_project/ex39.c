#include<stdio.h>
#define N 15
unsigned int a;
//输入的十一进制字符串存放在input中
char input[N];
//转换后的十四进制存放在s中
char s[N];
//m用来计算字符串长度
int m;
int main()
{
	//输入十一进制字符串存入input变量中
	scanf("%s", input);
	_asm{
		//取十一进制字符串首地址到edi中
		lea edi, input
		push edi
		//调用to_ten_value子程序把十一进制字符串转换为十进制数值形式，通过堆栈传入参数，返回值放入eax中
		call to_ten_value
		//mov m, eax
		//平衡堆栈
		add esp, 4
		
		//堆栈传递参数，第一个参数为十四进制字符串的首地址，第二个参数为十进制数值
		lea esi, s
		push esi
		push eax
		//调用to_14_str，10进制数值转14进制字符串
		call to_14_str
		//平衡堆栈
		add esp, 8
	}
	//printf("%d\n", m);
	printf("%s\n", s);
	return 0;

	_asm{
	//子程序：十一进制字符串转十进制数值
	//入口：堆栈传递十一进制字符串首地址
	//出口：eax = 十进制数值
to_ten_value:
		push ebp
		mov ebp, esp
		//十一进制字符串首地址存放到esi中
		mov esi, [ebp+8]
		//edx存放累加结果
		xor edx,edx
		//eax存放每次*11的结果
		xor eax,eax
lab1:
		imul edx, 11
		mov al, [esi]
		inc esi

		sub al, '0'
		//如果al是0-9则不需要处理
		cmp al, 10
		jb NN
		//al是A则通过减去7转换为10
		sub al, 7
NN:
		//累加结果存放到edx中
		add edx, eax
		//如果还有数字没有处理则继续处理，否则结束循环
		cmp [esi], 0
		jnz lab1
		//十一进制转十进制的数值存放到eax中
		mov eax, edx
		pop ebp
		ret
	}
	//子程序：十进制数值转换为十四进制字符串
	//入口：堆栈传递参数，第一个参数为十四进制字符串的首地址，第二个参数为十进制数值
	//出口：无
	_asm{
to_14_str:
		push ebp
		mov ebp, esp
		//....................mov not lea...................
		//esi存放转换后的十四进制字符串首地址
		//edi存放十进制数值
		mov esi, [ebp+12]
		mov edi, [ebp+8]

		xor ecx, ecx
		//除数为14
		mov ebx, 14
L1:
		//被除数低32位放入eax中
		mov eax, edi
		//被除数高32位置为0
		xor edx, edx
		//执行除法操作
		div ebx

		//余数转换为十四进制字符
		call Dxx

		//余数压入栈中
		push edx
		//计数
		inc ecx
		//商放入edi中作为下一次的低32位被除数
		mov edi, eax
		//edi为0则停止循环
		cmp edi, 0
		jne L1
		
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
		//子程序：把十进制的0-13转换为十四进制字符
		//入口：edx = 十进制数值
		//出口：edx = 十四进制字符
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
