#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main (int argc, char *argv[]) {
	srand(time(NULL));
	int r = rand();
	printf("The degrees %lf\n", r);
	FILE *fp;
	if((fp=fopen("rand.txt", "wb"))==NULL) {
	   printf("Cannot open file.\n");
	   exit(1);
	}
	fprintf(fp, "%f", r);
	fclose(fp);
	return 0;
}
