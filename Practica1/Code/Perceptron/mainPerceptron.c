#include "perceptron.h"


int main(int argc, char **argv)
{
	Perceptron perceptron;

	FILE *output = NULL;
	FILE *input = NULL;
	int i, j;
	float threshold = 0.8;
	/* comprueba la linea de comandos */
	for (i = 1; i < argc; i++)
	{
		if (strcmp("-input", argv[i])==0) {
			input = fopen(argv[i+1], "r");
		}
		else if (strcmp("-output", argv[i])==0) {
			output = fopen(argv[i+1], "w");
		}
	}

	if (input == NULL || output == NULL) {
		printf("USO: %s -input <f_entrada> -output <f_salida>\n", argv[0]);
		exit(0);
	}
	// createPerceptron(&perceptron,threshold,8,2);
	// deletePerceptron(&perceptron);

	Pattern patterns;
/*
	parser(input, &patterns);
	for(i=0;i<patterns.numPatterns;i++)
	{
		for(j=0;j<patterns.numAttributes;j++)
			printf("%.1f ",patterns.attributes[i][j]);

		for(j=0;j<patterns.numCategories;j++)
			printf("%d ",patterns.categories[i][j]);
		printf("\n");
	}

	printf("=======================\n");

	patternShuffle(&patterns,time(NULL));
*/
	createPattern(input, &patterns);
	for(i=0;i<patterns.numPatterns;i++)
	{
		for(j=0;j<patterns.numAttributes;j++)
			printf("%.1f ",patterns.attributes[i][j]);

		for(j=0;j<patterns.numCategories;j++)
			printf("%d ",patterns.categories[i][j]);
		printf("\n");
	}

	freePattern(&patterns);

	return 0;

}
