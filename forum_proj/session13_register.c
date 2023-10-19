#include <stdio.h>
int main() {
	register int reg = 1;
  	int* ptr = &reg;
	printf("the value of ptr is: %d", *ptr); //this will be an error
    return 0;
}