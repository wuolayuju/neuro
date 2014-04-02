

#include "autoencoder.h"


int main(int argc, char *argv[])

{
	int i;
	int n=0;
	FILE *output = NULL;
	/* comprueba la linea de comandos */
	for (i = 1; i < argc; i++)
	{
		if (strcmp("-output", argv[i])==0) {
			output = fopen(argv[i+1], "w");
		}
		else if (strcmp("-n", argv[i])==0) {
			n = atoi(argv[i+1]);
		}
	}
	
	if(output == NULL || n<=0)
	{
		printf("\nUSO: %s [-output <f_salida>] [-n <tamaño_rejilla>]\n\n", argv[0]);
		return 0;
	}

	construye_bd_autoencoder(n,output);

	return 1;
}