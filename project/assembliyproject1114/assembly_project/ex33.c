#include<stdio.h>
char input[100];
char output[100];
int main()
{
	scanf("%s", input);
	//程序中的循环是先执行后判断， 当字符串为空时程序可以正确执行
	_asm{
		//edi与ecx搭配用于从输入字符串中循环取字符处理
		//esi与edx搭配用于存储筛选出的字符
		lea esi, output
		lea edi, input
		xor ecx, ecx
		xor edx, edx
	L:
		//待处理的字符放入bl中
		mov bl, byte ptr [edi+ecx]
		//调用子程序判断该字符是否为英文字符
		call isletter
		//返回值eax为1则为英文字母需放入output中
		cmp eax, 1
		//返回值不等于1表明不需要处理，跳转到B代码处执行
		jne B
		//把bl中字符放入output中
		mov byte ptr[esi+edx], bl
		inc edx
	B:
		//取待处理字符串中的下一个字符
		inc ecx
		//判断字符串是否已经处理完
		cmp byte ptr [edi+ecx], 0
		jne L
	}
	printf("%s\n", output);
	return 0;
	_asm{
		//子程序：判断字母是否为小写
		//入口：bl = 单个字符
		//出口：eax (1表示是，0表示不是)
isletter:
		xor eax, eax
		//判断是否为小写字母	
		cmp bl, 'a'
		jb upper
		cmp bl, 'z'
		ja failed
		jmp ok
		//子程序：判断字母是否为大写
		//入口：bl = 单个字符
		//出口：eax (1表示是，0表示不是)
upper:
		//判断是否为大写字母
		cmp bl, 'A'
		jb failed
		cmp bl, 'Z'
		ja failed
	ok:
		inc eax
	failed:
		ret
	}
}
