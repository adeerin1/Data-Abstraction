#include <stdio.h>

int main() {
	FILE * f_ptr;
	f_ptr = fopen("example.txt","w+b");
	fclose(f_ptr);
	int i = 1;
	int i2 = 10;
	char a = 'a';
	char b = 'b';
	fwrite(&a,sizeof(char),1,f_ptr);
	fwrite(&b,sizeof(char),1,f_ptr);
	return 0;
}
