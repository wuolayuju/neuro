

#include "backpropagation.h"

int main(int argc, char **argv)
{

	FILE *output = NULL;
	FILE *outputDebug = NULL;
	FILE *inputLearn = NULL;
	FILE *inputExploit = NULL;
	float learnRate = 0.1;
	float fractionLearn = 0.3;
	int i;
	int numHiddenLayerNeurons = 2;
	float **weightsV = NULL;
	float **weightsW = NULL;	
	float *bias = NULL;	
	float errorTolerance = 0.05;
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
		if (strcmp("-outputDebug", argv[i])==0) {
			outputDebug = fopen(argv[i+1], "w");
		}
		else if (strcmp("-output", argv[i])==0) {
			output = fopen(argv[i+1], "w");
		}
		else if (strcmp("-learnrate", argv[i])==0) {
			learnRate = atof(argv[i+1]);
		}
		else if (strcmp("-part", argv[i])==0) {
			fractionLearn = atof(argv[i+1]);
		}
		else if (strcmp("-numNeurons", argv[i])==0) {
			numHiddenLayerNeurons = atoi(argv[i+1]);
		}
		else if (strcmp("-tolerance", argv[i])==0) {
			errorTolerance = atof(argv[i+1]);
		}
	}

	// Comprobamos los únicos dos argumentos obligatorios
	if (inputLearn == NULL || outputDebug ==NULL || (inputExploit!=NULL&&(output == NULL))) 
	{
		printf("\nUSO: %s [-inputLearn <f_entrada>] [-inputExploit <f_entrada> -output <f_salida>] [-outputDebug <f_debug>] [-tolerance <tolerancia>] [-numNeurons <numero_neuronas>] [-part <porcentaje_aprendizaje>] [-learnrate <tasa_aprendizaje>]\n\n", argv[0]);
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
	if(numHiddenLayerNeurons < 1)
	{
		fprintf(stderr, "ERROR: Numero de neuronas de la capa oculta ( >1 )\n");
		exit(0);
	}
	if (!createPattern(inputLearn, &patterns))
	{
		fprintf(stderr, "ERROR: Error en la lectura de patrones\n");
		exit(0);
	}

	fclose(inputLearn);

	weightsV = generateWeights(numHiddenLayerNeurons, patterns.numAttributes);
	weightsW = generateWeights(patterns.numCategories ,numHiddenLayerNeurons);


	bias = generateBias(numHiddenLayerNeurons,patterns.numCategories);

	debugWeight(weightsV,numHiddenLayerNeurons,patterns.numAttributes);
	debugWeight(weightsW,patterns.numCategories,numHiddenLayerNeurons);

	for(i=0;i<numHiddenLayerNeurons+patterns.numCategories;i++)
		printf("%.2f ",bias[i]);
	printf("\n");

	printf("\n##################LEARN##################\n");
	learnBackPropagation(weightsV, weightsW, bias, &patterns, 
	numHiddenLayerNeurons,learnRate,patterns.numPatterns*fractionLearn,errorTolerance, outputDebug);

	printf("\n##################TEST##################\n");	
	testBackPropagation(weightsV, weightsW, bias, &patterns, 
	numHiddenLayerNeurons,learnRate,(int)(patterns.numPatterns*fractionLearn) % patterns.numPatterns,
	 outputDebug);

	freeWeights(weightsW,patterns.numCategories);
	freeWeights(weightsV,numHiddenLayerNeurons);
	freePattern(&patterns);
	free(bias);

	return 1;
}