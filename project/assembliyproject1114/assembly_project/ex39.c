#include<stdio.h>
#define N 15
unsigned int a;
//�����ʮһ�����ַ��������input��
char input[N];
//ת�����ʮ�Ľ��ƴ����s��
char s[N];
//m���������ַ�������
int m;
int main()
{
	//����ʮһ�����ַ�������input������
	scanf("%s", input);
	_asm{
		//ȡʮһ�����ַ����׵�ַ��edi��
		lea edi, input
		push edi
		//����to_ten_value�ӳ����ʮһ�����ַ���ת��Ϊʮ������ֵ��ʽ��ͨ����ջ�������������ֵ����eax��
		call to_ten_value
		//mov m, eax
		//ƽ���ջ
		add esp, 4
		
		//��ջ���ݲ�������һ������Ϊʮ�Ľ����ַ������׵�ַ���ڶ�������Ϊʮ������ֵ
		lea esi, s
		push esi
		push eax
		//����to_14_str��10������ֵת14�����ַ���
		call to_14_str
		//ƽ���ջ
		add esp, 8
	}
	//printf("%d\n", m);
	printf("%s\n", s);
	return 0;

	_asm{
	//�ӳ���ʮһ�����ַ���תʮ������ֵ
	//��ڣ���ջ����ʮһ�����ַ����׵�ַ
	//���ڣ�eax = ʮ������ֵ
to_ten_value:
		push ebp
		mov ebp, esp
		//ʮһ�����ַ����׵�ַ��ŵ�esi��
		mov esi, [ebp+8]
		//edx����ۼӽ��
		xor edx,edx
		//eax���ÿ��*11�Ľ��
		xor eax,eax
lab1:
		imul edx, 11
		mov al, [esi]
		inc esi

		sub al, '0'
		//���al��0-9����Ҫ����
		cmp al, 10
		jb NN
		//al��A��ͨ����ȥ7ת��Ϊ10
		sub al, 7
NN:
		//�ۼӽ����ŵ�edx��
		add edx, eax
		//�����������û�д�������������������ѭ��
		cmp [esi], 0
		jnz lab1
		//ʮһ����תʮ���Ƶ���ֵ��ŵ�eax��
		mov eax, edx
		pop ebp
		ret
	}
	//�ӳ���ʮ������ֵת��Ϊʮ�Ľ����ַ���
	//��ڣ���ջ���ݲ�������һ������Ϊʮ�Ľ����ַ������׵�ַ���ڶ�������Ϊʮ������ֵ
	//���ڣ���
	_asm{
to_14_str:
		push ebp
		mov ebp, esp
		//....................mov not lea...................
		//esi���ת�����ʮ�Ľ����ַ����׵�ַ
		//edi���ʮ������ֵ
		mov esi, [ebp+12]
		mov edi, [ebp+8]

		xor ecx, ecx
		//����Ϊ14
		mov ebx, 14
L1:
		//��������32λ����eax��
		mov eax, edi
		//��������32λ��Ϊ0
		xor edx, edx
		//ִ�г�������
		div ebx

		//����ת��Ϊʮ�Ľ����ַ�
		call Dxx

		//����ѹ��ջ��
		push edx
		//����
		inc ecx
		//�̷���edi����Ϊ��һ�εĵ�32λ������
		mov edi, eax
		//ediΪ0��ֹͣѭ��
		cmp edi, 0
		jne L1
		
L2:
		pop edx
		//ת�����ֵ�����ַ�����
		mov [esi], dl
		inc esi
		//ecxΪ0ǡ�ô���
		loop L2
		//����ַ�����������
		mov [esi], 0
		pop ebp
		ret
		//�ӳ��򣺰�ʮ���Ƶ�0-13ת��Ϊʮ�Ľ����ַ�
		//��ڣ�edx = ʮ������ֵ
		//���ڣ�edx = ʮ�Ľ����ַ�
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
