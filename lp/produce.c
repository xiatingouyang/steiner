#include<stdio.h>


int main(int argc, char **argv){
	FILE * fp;
	int i;
	/* open the file for writing*/
	fp = fopen (arvg[1],"w");

	/* write 10 lines of text into the file stream*/
	for(i = 0; i < 10;i++){
		fprintf (fp, "This is line %d\n",i + 1);
	}

	/* close the file*/  
	fclose (fp);
	return 0;



	return 0;
}