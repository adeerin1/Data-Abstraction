#include <iostream>
#include <stdio.h>
using namespace std;

void accessFile(FILE *pfile) {
	FILE * pFile;
  	pFile = fopen ( "example.txt" , "w" );
  	fputs ( "First line of output" , pFile );
  	fseek ( pFile , 11 , SEEK_SET );
  	fputs ( "Second line" , pFile );
  	fclose ( pFile );
}


int main () {
FILE *pFile;
accessFile(pFile);


return 0;
}
