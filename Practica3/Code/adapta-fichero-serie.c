

#include "autoencoder.h"

#define MAX_LINE 256

int main(int argc, char *argv[])
{
	FILE *output, *input = NULL;
	int i, j;
	int np = 0;
	char string[MAX_LINE];
	int countElements = 0;
	float *elements = NULL;

	/* comprueba la linea de comandos */
	for (i = 1; i < argc; i++)
	{
		if (strcmp("-output", argv[i])==0) {
			output = fopen(argv[i+1], "w");
		}
		else if (strcmp("-input", argv[i])==0) {
			input = fopen(argv[i+1], "r");
		}
		else if (strcmp("-Np", argv[i])==0) {
			np = atoi(argv[i+1]);
		}
	}
	if(output == NULL || np<=0 || input == NULL)
	{
		printf("\nUSO: %s [-input <f_entrada>] [-output <f_salida>] [-Np <n_puntos>]\n\n", argv[0]);
		return 0;
	}

	while(fgets(string,MAX_LINE,input)!=NULL)
		countElements++;

	if(countElements == 0)
	{
		printf("Error in input file\n");
		fclose(output);
		fclose(input);		
		return 0;
	}
	elements = (float *)malloc(sizeof(float)*countElements);
	fseek(input,0l,SEEK_SET);

	for(i=0; i<countElements; i++)
		fscanf(input, "%f", &elements[i]);
	
	fprintf(output,"%d %d\n", np, 2);

	for (i=0; i<(countElements-np); i++){

		for (j=i; j<i+np; j++)
			 fprintf(output,"%.2f ", elements[j]);
	
		if (elements[j-1]<elements[j]) 
			fprintf(output,"1 0");

		else 
			fprintf(output,"0 1");

		fprintf(output,"\n");
	}


	fclose(output);
	fclose(input);
	return 1;
}