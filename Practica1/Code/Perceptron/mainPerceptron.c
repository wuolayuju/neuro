#include "perceptron.h"


int main(int argc, char **argv)
{
	Perceptron perceptron;

	FILE *output = NULL;
	FILE *input = NULL;
	int i;
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

	parser(input, &patterns);

	//freePattern(&patterns);

	return 0;

}
