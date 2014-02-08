#include <string.h>
#include "mccullochPitts.h"

int main(int argc, char **argv)
{
	Network net;
	boolean x1, x2, x3;
	FILE *output = NULL;
	FILE *input = NULL;
	int i;

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

	initNetworkMP(&net,2);

	while(parserBasic(input, &x1, &x2, &x3)) {
		feedNetworkMP(&net, x1, x2, x3);
		fprintf(output, "%d %d\n", 
			getOutputNetworkMP(&net, 0), 
			getOutputNetworkMP(&net, 1));
	}

	feedNetworkMP(&net, 0, 0, 0);
	fprintf(output, "%d %d\n", 
			getOutputNetworkMP(&net, 0), 
			getOutputNetworkMP(&net, 1));

	fclose(input);
	fclose(output);

	freeNetworkMP(&net);

	return 0;

}