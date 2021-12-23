#include "asm2.h"
double sin(double x, double eps) {

	double sin;
	__asm {
		finit

		//вычислим x = x - [x/2*pi]*2pi
		fldpi //pi
		fadd	st(0), st(0) //2pi
		fld		qword ptr x //2pi x
		fld		qword ptr x //2pi x x
		fdiv	st(0), st(2) //2pi x x/2pi
		frndint		//2pi x [x/2pi]
		fmul	st(0), st(2) //2pi x [x/2pi]*2pi
		fxch	st(1) //2pi [x/2pi]*2pi x
		fsub	st(0), st(1)
		fstp	x
		fstp	st(0)
		fstp	st(0)

		fld1 //1
		fld1 //1 1
		fld1 // 1 1 1

		fld		qword ptr x //1 1 1 x
		fldz // 1 1 1 x 0

		fld		qword ptr x// 1 1 1 x 0 x
		fld		qword ptr x// 1 1 1 x 0 x x
		xor		ecx, ecx
	LOOP_FOR_COMMON_TERM_SIN:
		xor		eax, eax

		fmul	st(0), st(1)// 1 1 1 x 0 x x^2
		fmul	st(0), st(1) // 1 1 1 x 0 x x^3

		fxch	st(2) // 1 1 1 x x^3 x 0
		fadd	st(0), st(2)// 1 1 1 x x^3 x x^3


		fxch	st(4)// 1 1 x^3 x x^3 x 1
		fadd	st(0), st(6)// 1 1 x^3 x x^3 x 2
		fmul	st(5), st(0)// 1 2 x^3 x x^3 x 2
		fadd	st(0), st(6)// 1 2 x^3 x x^3 x 3
		fmul	st(5), st(0)// 1 6 x^3 x x^3 x 3
		fxch	st(4) // 1 6 3 x x^3 x x^3

		fdiv	st(0), st(5)// 1 6 3 x x^3 x x^3/6

		fld		qword ptr eps
		fcom	st(1)
		fstp	eps
		jng		ACCURACY_OBTAINED
		jmp		ACCURACY_NOT_OBTAINED
	
	ACCURACY_OBTAINED:
		mov		eax, 1
	ACCURACY_NOT_OBTAINED:
		mov		edx, ecx
		and edx, 1
		cmp		edx, 0
		je		IS_ODD_SIN
		jmp		IS_EVEN_SIN

	IS_ODD_SIN :
		fchs // 1 6 3 x x^3 x -x^3/6 

	IS_EVEN_SIN :
		fadd	st(3), st(0) // 1 6 3 x-x^3/6 x^3 x -x^3/6 

		fsub	st(0), st(0) // 1 6 3 x-x^3/6 x^3 x 0
		fxch	st(2) // 1 6 3 x-x^3/6 0 x x^3 

		inc		ecx
		cmp		eax, 1
		je		STOP_LOOP
		jmp		LOOP_FOR_COMMON_TERM_SIN
	STOP_LOOP:
		fxch	st(3)
		fstp	qword ptr sin
	}
	return sin;
}
