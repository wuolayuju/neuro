#include "perceptron.h"


int main(int argc, char **argv)
{
	Perceptron perceptron;

	FILE *output = NULL;
	FILE *input = NULL;
	float fractionLearn = 0;
	float learnRate = 0.1;
	int i, j;
	float threshold = 0.8;
	Pattern patterns;

	/* comprueba la linea de comandos */
	for (i = 1; i < argc; i++)
	{
		if (strcmp("-input", argv[i])==0) {
			input = fopen(argv[i+1], "r");
		}
		else if (strcmp("-output", argv[i])==0) {
			output = fopen(argv[i+1], "w");
		}
		else if (strcmp("-part", argv[i])==0) {
			fractionLearn = atof(argv[i+1]);
		}
		else if (strcmp("-learnrate", argv[i])==0) {
			learnRate = atof(argv[i+1]);
		}
		else if (strcmp("-threshold", argv[i])==0) {
			threshold = atof(argv[i+1]);
		}
	}

	if (input == NULL || output == NULL) 
	{
		printf("USO: %s -input <f_entrada> -output <f_salida> [-part <porcentaje_aprendizaje>] [-learnrate <tasa_aprendizaje>] [-threshold <umbral>]\n", argv[0]);
		exit(0);
	}

	if ((fractionLearn < 0.0 || fractionLearn > 1) || (learnRate <= 0))
	{
		fprintf(stderr, "ERROR: Valor de porcentaje de aprendizaje (0,1] o factor de aprendizaje ( >0 )\n");
		exit(0);
	}

	if (!createPattern(input, &patterns))
	{
		fprintf(stderr, "ERROR: Error en la lectura de patrones\n");
		exit(0);
	}

	fclose(input);
	fclose(output);

	createPerceptron(&perceptron, threshold, patterns.numAttributes, 1);

	printf("\n##################LEARN##################\n");

	learnPerceptron(&perceptron, learnRate, threshold, &patterns, patterns.numPatterns*fractionLearn);

	printf("\n##################TEST##################\n");
	
	if(fractionLearn == 1)
		fractionLearn = 0;

	test(&perceptron, &patterns, patterns.numPatterns*fractionLearn);

	deletePerceptron(&perceptron);
	freePattern(&patterns);

	return 0;

}
