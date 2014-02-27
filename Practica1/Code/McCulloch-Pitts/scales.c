#include <string.h>
#include "mccullochPitts.h"

int main(int argc, char **argv)
{
	Network net;
	boolean x1, x2, x3;
	FILE *output = NULL;
	char outputPath[256];
	FILE *input = NULL;
	int i;

	/* Lectura de los argumentos de entrada */
	for (i = 1; i < argc; i++)
	{
		if (strcmp("-input", argv[i])==0) {
			input = fopen(argv[i+1], "r");
		}
		else if (strcmp("-output", argv[i])==0) {
			strcpy(outputPath, argv[i+1]);
			output = fopen(outputPath, "w");
		}
	}

	if (input == NULL || output == NULL) {
		printf("USO: %s -input <f_entrada> -output <f_salida>\n", argv[0]);
		exit(0);
	}

	/* Inicialización de la red con umbral = 2 */
	initNetworkMP(&net,2);

	/* Lectura de fichero y estímulo de la red con las entradas leídas */
	while(parserBasic(input, &x1, &x2, &x3)) {
		feedNetworkMP(&net, x1, x2, x3);
		fprintf(output, "%d %d\n", 
			getOutputNetworkMP(&net, 0), 
			getOutputNetworkMP(&net, 1));
	}

	/* Se realiza una excitación adicional para obtener la última salida */
	feedNetworkMP(&net, 0, 0, 0);
	printf("\nGenerando fichero %s ... ", outputPath);
	fprintf(output, "%d %d\n", 
			getOutputNetworkMP(&net, 0), 
			getOutputNetworkMP(&net, 1));

	fclose(input);
	fclose(output);

	printf("HECHO\n\n");

	freeNetworkMP(&net);

	return 0;

}