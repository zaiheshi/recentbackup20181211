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
		//��ջ���ݲ���
		push edi
		//ʮ�����ַ���תʮ������������ֵ����eax��
		call to_value
		//ƽ���ջ
		add esp, 4

		//esiΪת�����ʮ�������ַ����׵�ַ
		lea esi, s
		//��ջ���ݲ���s,a
		push esi
		push eax
		//10����ת16����
		call to_hex
		//ƽ���ջ
		add esp, 8
	}
	printf("%s\n", s);
	return 0;
	_asm{
	//�ӳ���ʮ�����ַ���ת��Ϊʮ������ֵ
	//��ڣ���ջ����ʮ�����ַ����׵�ַ
	//���ڣ�eax = ʮ������ֵ
to_value:
		push ebp
		mov ebp, esp
		//ʮ�����ַ����׵�ַ��ŵ�esi��
		mov esi, [ebp+8]
		xor edx,edx
		xor eax,eax
lab1:
		imul edx, 10
		//[esi]��ΧΪ��0��-��9��
		mov al, [esi]
		inc esi
		//ȥ��al��8λ��ֻȡ��8λ����Ҫת����ʮ�����ַ�
		and al, 0fh
		//�����ŵ�edx��
		add edx, eax
		//ת�����������ѭ��
		cmp [esi], 0
		jnz lab1
		//׼������ֵ
		mov eax, edx
		pop ebp
		ret
		}
	_asm{
		//�ӳ���ʮ������ֵת��Ϊʮ�������ַ���
		//��ڣ���ջ�еĲ�������Ϊת�����ʮ�������ַ����׵�ַ��ʮ������ֵ
		//���ڣ���
to_hex:
		push ebp
		mov ebp, esp
		//....................mov not lea...................
		//esiΪת�����ʮ�������ַ����׵�ַ
		mov esi, [ebp+12]
		//ediΪʮ������ֵ
		mov edi, [ebp+8]
		xor ecx, ecx
		//����Ϊ16
		mov ebx, 16
L1:
		//edx��eaxΪ������
		//��������32λ����eax��
		mov eax, edi
		//��������32λ��Ϊ0
		xor edx, edx

		div ebx
		call Dxx
		//����ѹ��ջ��
		push edx
		//����
		inc ecx

		//�̼��µĵ�32λ����������edi��
		mov edi, eax
		//ediΪ0��ֹͣѭ��
		cmp edi, 0
		jne L1
	
		//�Ѷ�ջ�е���������ȡ����s��
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
	//�ӳ���ʮ������ֵ(��ΧΪ0-15)תΪ16�����ַ�
	//��ڣ�edx = ʮ������ֵ
	//���ڣ�edx = ʮ�������ַ�
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
