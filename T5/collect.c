#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define PI 3.14159265

int main (int argc, char *argv[]) {
	
	char buf[1024];
	FILE *file;
	size_t nread;
	double result, valSin, valCos;
	file = fopen(argv[1], "r");
	if (file) {
		while ((nread = fread(buf, 1, sizeof buf, file)) > 0){
			printf("sin %s degrees\n", buf);
			valSin = atof(buf);
		}
		if (ferror(file)) {
			printf("Cannot open file.\n");
			exit(1);
		}
		fclose(file);
    }
	file = fopen(argv[2], "r");
	if (file) {
		while ((nread = fread(buf, 1, sizeof buf, file)) > 0){
			printf("sin %s degrees\n", buf);
			valCos = atof(buf);
		}
		if (ferror(file)) {
			printf("Cannot open file.\n");
			exit(1);
		}
		fclose(file);
    }
    result = pow(valSin, 2) + pow(valCos, 2);
    //result = valSin + valCos;
    printf("Collect %lf \n", result);
    FILE *fp;
    if((fp=fopen("collect.txt", "wb"))==NULL) {
	   printf("Cannot open file.\n");
	   exit(1);
	}
	fprintf(fp, "%f", result);
	fclose(fp);
	return 0;
}
