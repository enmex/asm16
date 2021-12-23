#include <stdio.h>
#include <assert.h>
#include "asm1.h"
#include "asm2.h"

void test_first() {

	printf("%s\n", deleteSubstr("aaabbcc", "bb", 7, 2));
	printf("%s\n", deleteSubstr("aaabbcc", "a", 7, 1));
	printf("%s\n", deleteSubstr("aaabbcc", "bb", 6, 2));
	printf("%s\n", deleteSubstr("aaabbcc", "bb", 7, 0));
	printf("%s\n", deleteSubstr("aaabbcc", "dd", 7, 2));
}

int main() {
	//test_first();

	//result = 1.83048772171
	printf("%f\n", sin(0.5, 1e-3));

	//result = inf
	printf("%f\n", sin(0, 1e-3));

	//result = 1
	printf("%f\n", sin(0.78539816339, 1e-3));

	//result = 1
	printf("%f\n", sin(1.57079632679, 1e-3));

	//result 
	printf("%f\n", sin(1e+9, 1e-3));
}