#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define PI 3.14159265

int main (int argc, char *argv[]) {
   double result, val;
   val = atof(argv[1]);
   result = sin(val * (PI / 180) );
   //result = sin(val);
   printf("The sine of %lf is %lf degrees\n", val, result);
   //return result;
   FILE *fp;
   if((fp=fopen("sin.txt", "wb"))==NULL) {
	   printf("Cannot open file.\n");
	   exit(1);
	}
	fprintf(fp, "%f", result);
	fclose(fp);
	return 0;
}
