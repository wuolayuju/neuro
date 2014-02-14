
#include "perceptron.h"

void initNeuron(Neuron *neuron, int id, int numConnections)
{
	neuron->id = id;
	neuron->weights = (float *)calloc(sizeof(float),numConnections);
	neuron->inputs = (float **)malloc(sizeof(float *)*numConnections);
	neuron->y = 0;
	neuron->numConnections = numConnections;
}

void freeNeuron(Neuron *neuron)
{
	if(neuron->inputs!=NULL)
	{
		free(neuron->weights);
		free(neuron->inputs);
		neuron->weights = NULL;
		neuron->inputs = NULL;
		neuron->numConnections = 0;
	}
}



void createPerceptron(Perceptron *p, float threshold, int numConnections, int numOutputs)
{
	//int i;

	p->threshold = threshold;
	p->numOutputs = numOutputs;

	p->inputs = (float *)malloc(sizeof(float)*numConnections);
	//p->outputs = (Neuron *)malloc(sizeof(Neuron)*numOutputs);
	//for(i=0;i<numOutputs;i++)
	//{
		initNeuron(&p->output,0,numConnections);
	//}


}

void deletePerceptron(Perceptron *p)
{

	freeNeuron(&p->output);
	free(p->inputs);
		
}


void transferFunction(Neuron *neuron, float threshold)
{

	int i;
	int y_in=0;

	for(i=0;i<neuron->numConnections;i++)
		y_in+= *neuron->inputs[i] * neuron->weights[i];

	if(y_in > threshold)
		neuron->y = 1;
	else if(y_in < -threshold)
		neuron->y = -1;
	else
		neuron->y = 0;
}

int parser(FILE *file, Pattern *pattern)
{
	int numAttributes, numCategories;
	char string[MAX_LINE];
	char tokens[ ] = " \n\t";
	char *ptr = NULL;
	int patternCount=0;
	int i;

	// Lectura del numero de atributos y clases del fichero
	fscanf(file, "%d %d\n", &numAttributes, &numCategories);
	if(numAttributes<=0 || numCategories<=0)
		return 0;

	// Reserva de memoria inicial para almacenar los patrones
	pattern->attributes = (float **)malloc(sizeof(float *)*INCR_SIZE_PATTERN);
	pattern->categories = (int **)malloc(sizeof(int *)*INCR_SIZE_PATTERN);

	for(i=0;i<INCR_SIZE_PATTERN;i++)
	{
		pattern->attributes[i]= (float *)malloc(sizeof(float)*numAttributes);
		pattern->categories[i]= (int *)malloc(sizeof(int)*numCategories);
	}
	
	while(fgets(string,MAX_LINE,file)!=NULL)
	{
		// Tokenizacion de los patrones
		ptr = strtok(string, tokens );
		pattern->attributes[patternCount][0] = atof(ptr); // Primera lectura especial

		for(i=1;i<numAttributes;i++)
		{
			ptr = strtok(NULL, tokens );
			pattern->attributes[patternCount][i] =atof(ptr);
		}

		for(i=0;i<numCategories;i++)
		{
			ptr = strtok(NULL, tokens );
			pattern->categories[patternCount][i] =  atoi(ptr);	
		}

		// Aumento de la memoria reservada para los patrones en caso necesario
		patternCount++;
		if ((patternCount % INCR_SIZE_PATTERN) == 0)
		{		
			pattern->attributes = (float **)realloc(pattern->attributes, sizeof(float *)*(INCR_SIZE_PATTERN+patternCount));
			pattern->categories = (int **)realloc(pattern->categories, sizeof(int *)*(INCR_SIZE_PATTERN+patternCount));

			for(i=patternCount; i < INCR_SIZE_PATTERN+patternCount ; i++)
			{
				pattern->attributes[i]= (float *)malloc(sizeof(float)*numAttributes);
				pattern->categories[i]= (int *)malloc(sizeof(int)*numCategories);
			}
		}
	}

	pattern->numAttributes = numAttributes;
	pattern->numCategories = numCategories;
	pattern->numPatterns = patternCount;

	return 1;
}

void freePattern(Pattern *pattern)
{
	int i;

	for (i = 0; i < pattern->numPatterns;i++)
	{
		free(pattern[i].attributes);
		free(pattern[i].categories);
	}
	free(pattern->attributes);
	free(pattern->categories);
	//free(pattern);
}

int learnPerceptron(
	Perceptron *perceptron, 
	float learningRate, 
	float threshold, 
	Pattern *patterns, 
	int numberPatterns)
{
	int p, i, w;
	boolean weightChange=false;

	do{

		weightChange = false;

		for (p = 0; p < numberPatterns; p++)
		{
			// Estimulacion de las entradas
			for (i = 0; i < perceptron->numInputs ; i++)
			{
				perceptron->inputs[i] = patterns->attributes[p][i];
			}

			// Aplicación de la función de transferencia
			transferFunction(&perceptron->output, perceptron->threshold);

			// Comprobación de error
			if ((perceptron->output.y == -1 && patterns->categories[p][0] == 1)
				|| (perceptron->output.y == 1 && patterns->categories[p][0] == 0))
			{
				weightChange = true;	
			}

			// Cambio en los pesos
			if (weightChange == true) {
				for (w = 0; w < perceptron->numInputs; w++)
				{
					if (patterns->categories[p][0] == 1)
						perceptron->output.weights[w] += learningRate * perceptron->inputs[w];

					if (patterns->categories[p][0] == 0)
					perceptron->output.weights[w] += -learningRate * perceptron->inputs[w];
				}
			}
      	}
	}while (weightChange);

	return 0;

}

int test(Perceptron *perceptron, FILE *file, int endFile)
{

	return 0;
}