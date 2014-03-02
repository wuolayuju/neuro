#include "perceptron.h"


int main(int argc, char **argv)
{
	Perceptron perceptron;

	FILE *output = NULL;
	FILE *inputLearn = NULL;
	FILE *inputExploit = NULL;
	float learnRate = 0.1;
	float fractionLearn = 0.3;
	int i;
	float threshold = 0;
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
		else if (strcmp("-learnrate", argv[i])==0) {
			learnRate = atof(argv[i+1]);
		}
		else if (strcmp("-threshold", argv[i])==0) {
			threshold = atof(argv[i+1]);
		}
		else if (strcmp("-part", argv[i])==0) {
			fractionLearn = atof(argv[i+1]);
		}
	}

	// Comprobamos los únicos dos argumentos obligatorios
	if (inputLearn == NULL || (inputExploit!=NULL&&(output == NULL))) 
	{
		printf("\nUSO: %s -inputLearn <f_entrada> [-inputExploit <f_entrada> -output <f_salida>] [-part <porcentaje_aprendizaje>] [-learnrate <tasa_aprendizaje>] [-threshold <umbral>]\n\n", argv[0]);
		exit(0);
	}

	if (learnRate <= 0)
	{
		fprintf(stderr, "ERROR: Valor de porcentaje de aprendizaje (0,1] o factor de aprendizaje ( >0 )\n");
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
	
	createPerceptron(&perceptron, threshold, patterns.numAttributes, 1);

	printf("\n##################LEARN##################\n");

	learnPerceptron(&perceptron, learnRate, threshold, &patterns, patterns.numPatterns*fractionLearn);
	fractionLearn = fractionLearn == 1 ? 0 : fractionLearn;
	printf("\n##################TEST##################\n");
	test(&perceptron, &patterns, patterns.numPatterns*fractionLearn);
	
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
