
#include "backpropagation.h"


void initWeights(float **weights, int weightsRow, int weightsColumn)
{

	int i, j;

	for(i=0;i<weightsRow;i++)
		for(j=0;j<weightsColumn;j++)
			weights[i][j] = getRandomNumberF(-0.5 , 0.5);
}

float **generateWeightsV(int numHidderLayerNeurons, int numAtributtes)
{
	int i;
	float **weights = (float **)malloc(sizeof(float *)*numHidderLayerNeurons);
	
	for(i=0;i<numAtributtes;i++)
		weights[i] = (float *)malloc(sizeof(float)*numAtributtes);

	initWeights(weights,numHidderLayerNeurons,numAtributtes);

	return weights;
}

float **generateWeightsW(int numHidderLayerNeurons, int numCategories)
{
	int i;
	float **weights = (float **)malloc(sizeof(float *)*numCategories);
	
	for(i=0;i<numCategories;i++)
		weights[i] = (float *)malloc(sizeof(float)*numHidderLayerNeurons);

	initWeights(weights,numCategories,numHidderLayerNeurons);

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

int learnBackPropagation(float **weightsV, float **weightsW, float *bias, Pattern *pattern, 
	int numHidderLayerNeurons, int numPatterns)
{

	int i, j, p;
	float *y_in = NULL;
	float *z_in = NULL;
	float *z = NULL;
	float *y = NULL;
	float **dV = NULL;
	float **dW = NULL;

	z_in = (float *)calloc(sizeof(float *),numHidderLayerNeurons);
	y_in = (float *)calloc(sizeof(float *),pattern->numCategories);

	for(p=0; p< numPatterns; p++)
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


		//FALTAN COSAS

		//Actualiza pesos (derrame cerebrall)
		for (i=0; i<pattern->numCategories; i++)
		{
			for (j=0; j<numHidderLayerNeurons; j++)
			{
				weightsW[i][j] += dW[i][j];
			}
		}	
		for (i=0; i<numHidderLayerNeurons; i++)
		{
			for (j=0; j<pattern->numAttributes; j++)
			{
				weightsV[i][j] += dV[i][j];
			}
		}
	}



	free(y);
	free(z);
	free(z_in);
	free(y_in);

	return 1;
}

