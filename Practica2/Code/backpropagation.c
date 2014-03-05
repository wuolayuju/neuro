
#include "backpropagation.h"


void initWeights(float **weights, int weightsRow, int weightsColumn)
{

	int i, j;

	for(i=0;i<weightsRow;i++)
		for(j=0;j<weightsColumn;j++)
			weights[i][j] = getRandomNumberF(-0.5 , 0.5);
}

float **generateWeights(int weightsRow, int weightsColumn)
{
	int i;
	float **weights = (float **)malloc(sizeof(float *)*weightsRow);
	
	for(i=0;i<weightsRow;i++)
		weights[i] = (float *)malloc(sizeof(float)*weightsColumn);

	initWeights(weights,weightsRow,weightsColumn);

	return weights;
}


float *generateBias(int numHidderLayerNeurons, int numCategories)
{
	int i;

	float *bias = (float *)malloc(sizeof(float)*(numHidderLayerNeurons + numCategories));

	for(i=0;i<(numHidderLayerNeurons + numCategories);i++)
		bias[i] = getRandomNumberF(-0.5 , 0.5); 

	return bias;
}

float function_bipolar(float in)
{
	return (2/(1+exp(-in)))-1;
}

float function_binary(float in)
{
	return 1/(1+exp(-in));
}

float dfunction_bipolar(float fx)
{
	return 0.5*(1 + fx)*(1 - fx);
}

float dfunction_binary(float fx)
{
	return fx*(1 - fx);
}

int learnBackPropagation(float **weightsV, float **weightsW, float *bias, Pattern *pattern, 
	int numHidderLayerNeurons, float learningRate, int numPatterns)
{

	int i, j, p;
	float *y_in = NULL;
	float *z_in = NULL;
	float *z = NULL;
	float *y = NULL;
	float *dk = NULL;
	float *d_inj = NULL;
	float *dj = NULL;
	float **Av = NULL;
	float **Aw = NULL;
	float *Ab = NULL;

	/*Neuron Inputs*/
	z_in = (float *)calloc(sizeof(float),numHidderLayerNeurons);
	y_in = (float *)calloc(sizeof(float),pattern->numCategories);

	/*Neuron Outputs*/
	z = (float *)calloc(sizeof(float),numHidderLayerNeurons);
	y = (float *)calloc(sizeof(float),pattern->numCategories);

	/*Errores*/
	dk = (float *)malloc(sizeof(float)*pattern->numCategories);
	d_inj = (float *)malloc(sizeof(float)*numHidderLayerNeurons);
	dj = (float *)malloc(sizeof(float)*numHidderLayerNeurons);


	/*Incrementos de peso*/
	Aw = (float **)malloc(sizeof(float *)*numHidderLayerNeurons);
	for(i=0;i<numHidderLayerNeurons;i++)
		Aw[i] = (float *)malloc(sizeof(float)*pattern->numCategories);

	Av = (float **)malloc(sizeof(float *)*pattern->numAttributes);
	for(i=0;i<pattern->numAttributes;i++)
		Av[i] = (float *)malloc(sizeof(float)*numHidderLayerNeurons);

	Ab = (float *)malloc(sizeof(float)*(numHidderLayerNeurons + pattern->numCategories));

	/*Learn*/
	for(p=0; p < numPatterns; p++)
	{
		/*Propagación palante*/
		for (i=0; i<numHidderLayerNeurons; i++)
		{
			z_in[i] = bias[i];
			for (j=0; j<pattern->numAttributes; j++)
				z_in[i] += weightsV[i][j] * pattern->attributes[p][j];
			
			z[i] = function_bipolar(z_in[i]);
		}

		for (i=0; i<pattern->numCategories; i++)
		{
			y_in[i] = bias[numHidderLayerNeurons+i];
			for (j=0; j<numHidderLayerNeurons; j++)
				y_in[i] += weightsW[i][j]*z[j];
			
			y[i] = function_bipolar(y_in[i]);
		}

		// Calculo del error en neuronas de salida
		// y del incremento de los pesos
		for(i=0;i<pattern->numCategories;i++)
		{
			dk[i] = (pattern->attributes[p][i] - y[i])*dfunction_bipolar(y[i]);
			
			for(j=0;j<numHidderLayerNeurons;j++)
				Aw[j][i] = learningRate*dk[i]*z[j]; 

			Ab[numHidderLayerNeurons+i] = learningRate*dk[i];
		}


		//Retropropagación
		//FALTAN COSAS

		//Actualiza pesos (derrame cerebrall)
		for (i=0; i<pattern->numCategories; i++)
		{
			for (j=0; j<numHidderLayerNeurons; j++)
			{
				weightsW[i][j] += Aw[i][j];
			}
		}	
		for (i=0; i<numHidderLayerNeurons; i++)
		{
			for (j=0; j<pattern->numAttributes; j++)
			{
				weightsV[i][j] += Av[i][j];
			}
		}
	}

	free(y);
	free(z);
	free(z_in);
	free(y_in);
	free(dk);
	free(Ab);
	for(i=0;i<numHidderLayerNeurons;i++)
		free(Aw[i]);
	free(Aw);
	for(i=0;i<pattern->numAttributes;i++)
		free(Av[i]);
	free(Av);

	return 1;
}

