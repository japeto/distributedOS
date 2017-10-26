#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define PI 3.14159265

int main (int argc, char *argv[]) {
   double result, valSin;
	file = fopen("rand.txt", "r");
	if (file) {
		while ((nread = fread(buf, 1, sizeof buf, file)) > 0){
			printf("rand %s degrees\n", buf);
			valSin = atof(buf);
		}
		if (ferror(file)) {
			printf("Cannot open file.\n");
			exit(1);
		}
		fclose(file);
    }
   result = sin(valSin * (PI / 180) );
   printf("The sin of %lf is %lf degrees\n", valSin, result);
   FILE *fp;
   if((fp=fopen("sin.txt", "wb"))==NULL) {
	   printf("Cannot open file.\n");
	   exit(1);
	}
	fprintf(fp, "%f", result);
	fclose(fp);
	return 0;
}
