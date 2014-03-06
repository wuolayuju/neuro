
#include "backpropagation.h"


/******************************************************************************
Purpose:

	Init the weights between [-0.5, 0.5]

Author:

	Ari Handler Adrián Lorenzo

Parameters:

	weights
	weighsRow
	weightsColumn
******************************************************************************/
void initWeights(float **weights, int weightsRow, int weightsColumn)
{

	int i, j;

	for(i=0;i<weightsRow;i++)
		for(j=0;j<weightsColumn;j++)
			weights[i][j] = getRandomNumberF(-0.5 , 0.5);
}
/******************************************************************************
Purpose:

	Return the matrix of weights of a neuronal network

Author:

	Ari Handler Adrián Lorenzo

Parameters:

	weights
	weighsRow

******************************************************************************/
float **generateWeights(int weightsRow, int weightsColumn)
{
	int i;
	float **weights = (float **)malloc(sizeof(float *)*weightsRow);
	
	for(i=0;i<weightsRow;i++)
		weights[i] = (float *)malloc(sizeof(float)*weightsColumn);

	initWeights(weights,weightsRow,weightsColumn);

	return weights;
}

void debugWeight(float **weight, int row, int column)
{
	int i,j;

	for(i=0;i<row;i++)
	{
		for(j=0;j<column;j++)
			printf("%.2f ",weight[i][j]);		
		printf("\n");
	}

	
}	
/******************************************************************************
Purpose:

	Return the array of bias of a neuronal network
	Each neuron have a bias
	Number of bias = numHiddenLayerNeurons + numCategories
Author:

	Ari Handler Adrián Lorenzo

Parameters:

	numHiddenLayerNeurons
	numCategories

******************************************************************************/
float *generateBias(int numHiddenLayerNeurons, int numCategories)
{
	int i;

	float *bias = (float *)malloc(sizeof(float)*(numHiddenLayerNeurons + numCategories));

	for(i=0;i<(numHiddenLayerNeurons + numCategories);i++)
		bias[i] = getRandomNumberF(-0.5 , 0.5); 

	return bias;
}
/******************************************************************************
Purpose:

	free a matrix of weights of a neuronal network

Author:

	Ari Handler Adrián Lorenzo

Parameters:

	weights
	weightsRow

******************************************************************************/
void freeWeights(float **weights, int weightsRow)
{
	int i;

	for(i=0;i<weightsRow;i++)
		free(weights[i]);

	free(weights);

}
/******************************************************************************
Purpose:

	Calculates the value of bipolar sigmoidal function

Author:

	Ari Handler Adrián Lorenzo

Parameters:

	in

******************************************************************************/
float function_bipolar(float in)
{
	return (2/(1+exp(-in)))-1;
}
/******************************************************************************
Purpose:

	Calculates the value of binary sigmoidal function

Author:

	Ari Handler Adrián Lorenzo

Parameters:

	in

******************************************************************************/
float function_binary(float in)
{
	return 1/(1+exp(-in));
}
/******************************************************************************
Purpose:

	Calculates the value of bipolar sigmoidal derived function

Author:

	Ari Handler Adrián Lorenzo

Parameters:

	fx

******************************************************************************/
float dfunction_bipolar(float fx)
{
	return 0.5*(1 + fx)*(1 - fx);
}
/******************************************************************************
Purpose:

	Calculates the value of binary sigmoidal derived function

Author:

	Ari Handler Adrián Lorenzo

Parameters:

	fx

******************************************************************************/
float dfunction_binary(float fx)
{
	return fx*(1 - fx);
}
/******************************************************************************
Purpose:

	Calculates the value of bipolar sigmoidal derived function

Author:

	Ari Handler Adrián Lorenzo

Parameters:

	weightsV
	weightsW
	bias
	pattern 
	numHiddenLayerNeurons
	learnRate
	numPatterns
	tolerance

******************************************************************************/
int learnBackPropagation(float **weightsV, float **weightsW, float *bias, Pattern *pattern, 
	int numHiddenLayerNeurons, float learnRate, int numPatterns, float tolerance)
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

	int n_iter = 0;
	float RMS;

	/**ALLOC BLOCK**/
	
	/*Neuron Inputs*/
	z_in = (float *)calloc(sizeof(float),numHiddenLayerNeurons);
	y_in = (float *)calloc(sizeof(float),pattern->numCategories);

	/*Neuron Outputs*/
	z = (float *)calloc(sizeof(float),numHiddenLayerNeurons);
	y = (float *)calloc(sizeof(float),pattern->numCategories);

	/*Errores*/
	dk = (float *)malloc(sizeof(float)*pattern->numCategories);
	d_inj = (float *)malloc(sizeof(float)*numHiddenLayerNeurons);
	dj = (float *)malloc(sizeof(float)*numHiddenLayerNeurons);

	/*Incrementos de peso*/
	Aw = (float **)malloc(sizeof(float *)*pattern->numCategories);
	for(i=0;i<pattern->numCategories;i++)
		Aw[i] = (float *)malloc(sizeof(float)*numHiddenLayerNeurons);

	Av = (float **)malloc(sizeof(float *)*numHiddenLayerNeurons);
	for(i=0;i<numHiddenLayerNeurons;i++)
		Av[i] = (float *)malloc(sizeof(float)*pattern->numAttributes);

	Ab = (float *)malloc(sizeof(float)*(numHiddenLayerNeurons + pattern->numCategories));

	/**LEARN BLOCK**/
	do
	{
		RMS = 0;

		for(p=0; p < numPatterns; p++)
		{
			/*Propagación palante*/
			for (i=0; i<numHiddenLayerNeurons; i++)
			{
				z_in[i] = bias[i];
				for (j=0; j<pattern->numAttributes; j++)
					z_in[i] += weightsV[i][j] * pattern->attributes[p][j];
				
				z[i] = function_bipolar(z_in[i]);
				if(DEBUG_TEST)
					printf("Z[%d] = %.2f\n",i,z[i]);
			}

			for (i=0; i<pattern->numCategories; i++)
			{
				y_in[i] = bias[numHiddenLayerNeurons+i];
				for (j=0; j<numHiddenLayerNeurons; j++)
					y_in[i] += weightsW[i][j]*z[j];
				if(DEBUG_TEST)
					printf("Y_IN %.2f\n",y_in[i]);
				y[i] = function_bipolar(y_in[i]);
				if(DEBUG_TEST)
					printf("Y[%d] = %.2f\n",i,y[i]);
			}

			// Calculo del error en neuronas de salida
			// y del incremento de los pesos
			for(i=0;i<pattern->numCategories;i++)
			{
				dk[i] = (pattern->categories[p][i] - y[i])*dfunction_bipolar(y[i]);
				if(DEBUG_TEST)
					printf("%.2f %.2f %.2f\n",pattern->attributes[p][i],y[i],
					dfunction_bipolar(y[i]));
				if(DEBUG_TEST)
					printf("DK[%d] = %.2f\n",i,dk[i]);

				for(j=0;j<numHiddenLayerNeurons;j++)
				{
					Aw[i][j] = learnRate*dk[i]*z[j];
					if(DEBUG_TEST)
						printf("Aw[%d][%d] = %.2f\n",i,j,Aw[i][j]);
				}
				Ab[numHiddenLayerNeurons+i] = learnRate*dk[i];

				if(DEBUG_TEST)
					printf("Ab[%d] = %.2f\n",numHiddenLayerNeurons+i,
					Ab[numHiddenLayerNeurons+i]);
			}

			for (i=0; i<numHiddenLayerNeurons; i++){

				for (j=0; j<pattern->numCategories; j++)
				{
					d_inj[i]+=dk[j]*weightsW[j][i];
					if(DEBUG_TEST)
						printf("%.3f %.3f\n",dk[j],weightsW[j][i]);
					if(DEBUG_TEST)
						printf("D_IN[%d] = %.3f\n",i,d_inj[i]);
				}

				dj[i] = d_inj[i]*dfunction_bipolar(z[i]);
				if(DEBUG_TEST)
					printf("D_J[%d] = %.3f\n",i,dj[i]);

				for (j=0; j<pattern->numAttributes; j++)
				{
					Av[i][j]=learnRate*dj[i]*pattern->attributes[p][j];
					if(DEBUG_TEST)
						printf("Av[%d][%d] = %.3f\n",i,j,Av[i][j]);
				}
				Ab[i]=learnRate*dj[i];

				if(DEBUG_TEST)
					printf("Ab[%d] = %.3f\n",i,Ab[i]);
			}


			//Retropropagación
			//FALTAN COSAS

			//Actualiza pesos (derrame cerebrall)
			for (i=0; i<pattern->numCategories; i++)
			{
				for (j=0; j<numHiddenLayerNeurons; j++)
				{
					if(DEBUG_TEST)
						printf("BEFORE w[%d][%d] = %.4f\n",i,j,weightsW[i][j]);
					weightsW[i][j] += Aw[i][j];
					if(DEBUG_TEST)
						printf("AFTER w[%d][%d] = %.4f\n",i,j,weightsW[i][j]);
				}
			}	
			for (i=0; i<numHiddenLayerNeurons; i++)
			{
				for (j=0; j<pattern->numAttributes; j++)
				{
					if(DEBUG_TEST)
						printf("BEFORE v[%d][%d] = %.4f\n",i,j,weightsV[i][j]);
					weightsV[i][j] += Av[i][j];
					if(DEBUG_TEST)
						printf("AFTER v[%d][%d] = %.4f\n",i,j,weightsV[i][j]);
				}
			}
			for (i=0;i<numHiddenLayerNeurons+pattern->numCategories;i++)
			{
				if(DEBUG_TEST)
					printf("BEFORE b[%d] = %.4f\n",i,bias[i]);
				bias[i]+=Ab[i];
				if(DEBUG_TEST)
					printf("AFTER b[%d] = %.4f\n",i,bias[i]);
			}

			for(i=0;i<pattern->numCategories;i++)
				RMS += pow(pattern->categories[p][i] - y[i], 2)/numPatterns;
			
		}
		n_iter++;
		printf("Epoca %d, RMS = %.5f\n",n_iter,RMS);
		if(n_iter>=NUM_MAX_ITER)
			break;
	}while(RMS>tolerance);


	/**FREE BLOCK**/
	free(y);
	free(z);
	free(z_in);
	free(y_in);
	free(dk);
	free(Ab);

	for(i=0;i<pattern->numCategories;i++)
		free(Aw[i]);
	free(Aw);

	for(i=0;i<numHiddenLayerNeurons;i++)
		free(Av[i]);
	free(Av);

	return 1;
}

int testBackPropagation(float **weightsV, float **weightsW, float *bias, Pattern *pattern, 
	int numHiddenLayerNeurons, float learnRate, int numFirstPattern)
{
	int p,i,j;
	float *y_in = NULL;
	float *z_in = NULL;
	float *z = NULL;
	float *y = NULL;


	/*Neuron Inputs*/
	z_in = (float *)calloc(sizeof(float),numHiddenLayerNeurons);
	y_in = (float *)calloc(sizeof(float),pattern->numCategories);

	/*Neuron Outputs*/
	z = (float *)calloc(sizeof(float),numHiddenLayerNeurons);
	y = (float *)calloc(sizeof(float),pattern->numCategories);

	for(p=numFirstPattern; p<pattern->numPatterns ;p++)
	{

		/*Propagación palante*/
		for (i=0; i<numHiddenLayerNeurons; i++)
		{
			z_in[i] = bias[i];
			for (j=0; j<pattern->numAttributes; j++)
				z_in[i] += weightsV[i][j] * pattern->attributes[p][j];
			
			z[i] = function_bipolar(z_in[i]);
			printf("Z[%d] = %.2f\n",i,z[i]);
		}

		for (i=0; i<pattern->numCategories; i++)
		{
			y_in[i] = bias[numHiddenLayerNeurons+i];
			for (j=0; j<numHiddenLayerNeurons; j++)
				y_in[i] += weightsW[i][j]*z[j];
			printf("Y_IN %.2f\n",y_in[i]);
			y[i] = function_bipolar(y_in[i]);
			printf("T[%d] = %d Y[%d] = %.2f\n",i,pattern->categories[p][i],i,y[i]);
		}

	}

	free(y);
	free(z);
	free(z_in);
	free(y_in);

	return 1;
}

