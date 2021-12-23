#include <stdlib.h>
#include <stdio.h>

char* deleteSubstr(char* str, char* substr, int size_str, int size_substr) {

	char* result;
	int result_size;

	__asm {
		//��������� ��� ������ �� ������
		mov		eax, str //����������� �������� ������
		cmp		eax, 0   //��������� ��� ��� �������
		je		NULL_STRING //���� ��� �������, �� ������������ �� ���� �����

		//��������� ��� ��������� �� ������
		mov		eax, substr
		cmp		eax, 0
		je		NULL_STRING

		//��������� ��� ������� �� ������
		mov		eax, size_str
		cmp		eax, 0
		je		EMPTY_SIZE

		mov		eax, size_substr
		cmp		eax, 0
		je		EMPTY_SIZE

		xor		ebx, ebx
		mov		esi, str
		mov 	edi, substr
		
	CYCLE:
		xor		ecx, ecx
		cmp		ebx, size_str
		je		SUBSTR_NOT_FOUND

		mov		dl, [esi][ebx]
		cmp		[edi][ecx], dl
		je		CHECK_FOR_SUBSTR

		inc		ebx
		jmp		CYCLE

	CHECK_FOR_SUBSTR:
		cmp		ecx, substr
		je		GET_SUBSTR_POS

		inc		ebx
		inc		ecx

		mov		dl, [esi][ebx]
		cmp		[edi][ecx], dl
		je		CHECK_FOR_SUBSTR

		cmp		ebx, size_str
		jne		GET_SUBSTR_POS
		jmp		SUBSTR_NOT_FOUND

	GET_SUBSTR_POS:
		sub		ebx, ecx

		//�������� ������ ��� ����������
		mov		eax, size_str
		sub		eax, size_substr
		mov		result_size, eax
		inc		eax //��� ��� ������� \0
		push    eax
		call    malloc
		add     esp, 4

		//���� ���������� ���� ������ �� ����������� ���������
		cmp     eax, 0
		je      MALLOC_NULL

		xor		edi, edi
		xor		ecx, ecx
		jmp		CYCLE_FOR_RESULT_BEFORE_SKIP

	CYCLE_FOR_RESULT_BEFORE_SKIP:
		cmp		ecx, ebx
		je		SKIP_SUBSTR

		mov		dl, [esi][ecx]
		mov		[eax][edi], dl

		inc		edi
		inc		ecx
		jmp		CYCLE_FOR_RESULT_BEFORE_SKIP

	SKIP_SUBSTR:
		add		ecx, size_substr
		jmp		CYCLE_FOR_RESULT_AFTER_SKIP

	CYCLE_FOR_RESULT_AFTER_SKIP:
		cmp		ecx, size_str
		je		ADD_NULL_CHAR

		mov		dl, [esi][ecx]
		mov		[eax][edi], dl

		inc		edi
		inc		ecx
		jmp		CYCLE_FOR_RESULT_AFTER_SKIP

	SUBSTR_NOT_FOUND:
		jmp		END_SUBSTR_NOT_FOUND

	ADD_NULL_CHAR:
		mov		byte ptr [eax][edi], '\0' //��������� ������ ��������� ������
		jmp		END

	NULL_STRING:
		jmp		END

	MALLOC_NULL:
		jmp		END

	EMPTY_SIZE:
		mov		eax, str
		mov		result, eax
		jmp		END_OF_PROGRAMM

	END:
		mov		result, eax
		jmp		END_OF_PROGRAMM

	END_SUBSTR_NOT_FOUND:
		mov		result, esi
		jmp		END_OF_PROGRAMM

	END_OF_PROGRAMM:
	}
	return result;
}