#include "perceptron.h"


int main(int argc, char **argv)
{
	Perceptron perceptron;

	FILE *output = NULL;
	FILE *inputLearn = NULL;
	FILE *inputTest = NULL;
	float learnRate = 0.1;
	int i;
	float threshold = 0.8;
	Pattern patterns;

	/* comprueba la linea de comandos */
	for (i = 1; i < argc; i++)
	{
		if (strcmp("-inputLearn", argv[i])==0) {
			inputLearn = fopen(argv[i+1], "r");
		}
		if (strcmp("-inputTest", argv[i])==0) {
			inputTest = fopen(argv[i+1], "r");
		}
		else if (strcmp("-output", argv[i])==0) {
			output = fopen(argv[i+1], "w");
		}
		else if (strcmp("-learnrate", argv[i])==0) {
			learnRate = atof(argv[i+1]);
		}
		else if (strcmp("-threshold", argv[i])==0) {
			threshold = atof(argv[i+1]);
		}
	}

	if (inputLearn == NULL || output == NULL || inputTest == NULL) 
	{
		printf("USO: %s -inputLearn <f_entrada> -inputTest <f_entrada> -output <f_salida> [-learnrate <tasa_aprendizaje>] [-threshold <umbral>]\n", argv[0]);
		exit(0);
	}

	if (learnRate <= 0)
	{
		fprintf(stderr, "ERROR: Valor de porcentaje de aprendizaje (0,1] o factor de aprendizaje ( >0 )\n");
		exit(0);
	}

	if (!createPattern(inputLearn, &patterns))
	{
		fprintf(stderr, "ERROR: Error en la lectura de patrones\n");
		exit(0);
	}

	fclose(inputLearn);
	

	createPerceptron(&perceptron, threshold, patterns.numAttributes, 1);

	printf("\n##################LEARN##################\n");

	learnPerceptron(&perceptron, learnRate, threshold, &patterns, patterns.numPatterns);

	freePattern(&patterns);

	printf("\n##################TEST##################\n");
	
	if (!createPattern(inputTest, &patterns))
	{
		fprintf(stderr, "ERROR: Error en la lectura de patrones\n");
		exit(0);
	}	
	printTest(&perceptron, &patterns, 0, output);

	fclose(output);
	fclose(inputTest);
	deletePerceptron(&perceptron);
	freePattern(&patterns);

	return 0;

}
