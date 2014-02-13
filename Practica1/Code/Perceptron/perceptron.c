
#include "perceptron.h"

/*
void createPerceptron(Perceptron *p, int numConnections, int numOutputs)
{
	p->numConnections = numConnections;
	p->numOutputs = numOutputs;

	p->inputs = (int *)malloc(sizeof(int)*numConnections);
	p->weights = (int *)calloc(sizeof(int),numConnections);
	p->outputs = (int *)malloc(sizeof(int)*numOutputs);
}*/
/*
void deletePerceptron(Perceptron *p)
{
	free(p->inputs);
	free(p->weights);
	free(p->outputs);	
}
*/

void transferFunction(Neuron *neuron, float threshold)
{

	int i;
	int y_in=0;

	for(i=0;i<neuron->numConnections;i++)
		y_in+= *neuron->inputs[i] * neuron->weights[i];

	if(y_in>threshold)
		neuron->y = 1;
	else if(y_in<-threshold)
		neuron->y = -1;
	else
		neuron->y = 0;
}

int learn(Perceptron *perceptron, float learningRate, float threshold, FILE *file, int endFile)
{
	int numConnections, numOutputs;
	int p, i, w, patternCount;
	int **y;
	int **x;
	boolean weightChange=false;

	fscanf(file, "%d %d\n", &numConnections, &numOutputs);

	y = (int **)malloc(sizeof(int *) * patternCount);
	x = (int **)malloc(sizeof(int *) * patternCount);
	for(i=0;i<patternCount;i++)
	{
		y[i] = (int *)malloc(sizeof(int) * numOutputs);
		x[i] = (int *)malloc(sizeof(int) * numConnections);
	}

	//createPerceptron(p,numConnections,numOutputs);

	/*lee el patron y obtiene el numero de patrones patternCount*/

	do{
		for (p = 0; p < patternCount; p++)
		{
			for(i=0;i<numOutputs;i++)
			{
				transferFunction(&perceptron->outputs[i],perceptron->threshold);
				if(y[p][i] != perceptron->outputs[i].y)
				{
					weightChange = true;
					for(w=0;w < perceptron->outputs[w].numConnections; w++)
						perceptron->outputs[i].weights[w] += learningRate * y[p][i] * x[p][w];
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