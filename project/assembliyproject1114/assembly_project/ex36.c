#include<stdio.h>
#define N 100
char c;
char s[N];
int main()
{
	//��ȡ�ַ���c��
	scanf("%c", &c);
	_asm{
		//ת����Ķ������ַ����׵�ַ
		lea esi, s
		xor ax, ax
		//�����ַ��ŵ�al��
		mov al, c	
		//to_ascIIʵ�ְ��ַ�ת��ΪascII�������ֵ������ֵ�����esi�У����üĴ���(esi�� al)���ݲ���
		call to_ascII
	}
	printf("ת����Ķ�����ֵ%s\n", s);
	return 0;
	_asm{
		//�ӳ��򣺵����ַ�ת��Ϊ��Ӧ��ascii��Ķ������ַ���
		//��ڣ�al = �ַ���esi = ת����Ķ������ַ����׵�ַ
		//���ڣ���
to_ascII:
		//�ܹ�ѭ��8��
		mov ecx, 8
L:
		//ѭ������1λ
		rol al, 1
		mov bl, al
		//ȡ���һλ��01h��������ó���ǰλ������
		and bl, 01h
		//תΪ��Ӧ�������ַ�'0' or '1'
		add bl, 30h
		//����s��
		mov [esi], bl
		inc esi
		loop L
		//����ַ���������־
		mov [esi], 0
		ret
}
}
