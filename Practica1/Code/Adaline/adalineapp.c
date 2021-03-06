#include "adaline.h"


int main(int argc, char **argv)
{
	Perceptron perceptron;

	FILE *output = NULL;
	FILE *inputLearn = NULL;
	FILE *inputExploit = NULL;
	float fractionLearn = 0;
	float learnRate = 0.1;
	float errorTolerance = 0.1;
	int i;
	float threshold = 0.8;
	Pattern patterns;

	/* comprueba la linea de comandos */
	for (i = 1; i < argc; i++)
	{
		if (strcmp("-inputLearn", argv[i])==0) {
			inputLearn = fopen(argv[i+1], "r");
		}
		if (strcmp("-inputExploit", argv[i])==0) {
			inputExploit = fopen(argv[i+1], "r");
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
		else if (strcmp("-tolerance", argv[i])==0) {
			errorTolerance = atof(argv[i+1]);
		}
	}

	if (inputLearn == NULL || (inputExploit!=NULL&&(output == NULL))) 
	{
		printf("\nUSO: %s -inputLearn <f_entrada> [-inputExploit <f_entrada> -output <f_salida>] [-tolerance <tolerancia>] [-part <porcentaje_aprendizaje>] [-learnrate <tasa_aprendizaje>] [-threshold <umbral>]\n\n", argv[0]);
		exit(0);
	}

	if ((fractionLearn < 0.0 || fractionLearn > 1) || (learnRate <= 0))
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

	createPerceptron(&perceptron, 0, patterns.numAttributes, 1);
	initWeightsAdaline(&perceptron);

	printf("\n##################LEARN##################\n");

	learnAdaline(&perceptron, learnRate, threshold, &patterns, 
		patterns.numPatterns*fractionLearn, errorTolerance);

	printf("\n##################TEST##################\n");

	test(&perceptron, &patterns, ((int)(patterns.numPatterns*fractionLearn)) % patterns.numPatterns);
	if (inputExploit != NULL) {

		printf("\n##################EXPLOIT##################\n");

		freePattern(&patterns);

		if (!createPatternExploit(inputExploit, &patterns))
		{
			fprintf(stderr, "ERROR: Error en la lectura de patrones\n");
			exit(0);
		}
		printTest(&perceptron, &patterns, 0, output);
		fclose(inputExploit);
		fclose(output);
	}
	deletePerceptron(&perceptron);
	freePattern(&patterns);

	return 0;

}
