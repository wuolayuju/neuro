
#include "mccullochPitts.h"



int parserBasic(FILE *inputFile, boolean *x1, boolean *x2, boolean *x3)
{
	char string[MAX_LINE];

	if(fgets(string,MAX_LINE,inputFile)!=NULL)
	{
		if(sscanf(string,"%d %d %d\n",x1,x2,x3)!=3)
			return 0;

			
		printf("Xs %d %d %d\n",*x1,*x2,*x3);
		return 1;
	}

	return 0;

}

int parser(FILE *inputFile,boolean inputs[][3])
{
	int times=0;

	while(parserBasic(inputFile,&inputs[times][0],&inputs[times][1],&inputs[times][2]))
		times++;

	return times;

}

void initNeuron(Neuron *neuron)
{
	neuron->weights = NULL;
	neuron->inputs = NULL;
	neuron->y = 0;
	neuron->numConnections = 0;

}

void initNetworkMP(Network *net, int x1, int x2, int x3)
{
	int i;

	initNeuron(&net->outputNeurons[0]);
	initNeuron(&net->outputNeurons[1]);
	
	initNeuron(&net->fstHiddenLayer[0]);
	initNeuron(&net->fstHiddenLayer[1]);
	initNeuron(&net->fstHiddenLayer[2]);

	for(i=0;i<6;i++)
		initNeuron(&net->scndHiddenLayer[i]);

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

void freeNetworkMP(Network *net)
{
	int i;
	
	freeNeuron(&net->outputNeurons[0]);
	freeNeuron(&net->outputNeurons[1]);
	
	freeNeuron(&net->fstHiddenLayer[0]);
	freeNeuron(&net->fstHiddenLayer[1]);
	freeNeuron(&net->fstHiddenLayer[2]);

	for(i=0;i<6;i++)
		freeNeuron(&net->scndHiddenLayer[i]);
}


void addConnection(Neuron *neuron, Neuron *input, int weight)
{
	if(neuron->inputs == NULL)
	{
		neuron->inputs = (int **)malloc(sizeof(int));
		neuron->weights = (int *)malloc(sizeof(int));
		
	}
	else
	{
		neuron->inputs = (int **)realloc(neuron->inputs, neuron->numConnections+1 * sizeof(int));
		neuron->weights = (int *)realloc(neuron->weights, neuron->numConnections+1 * sizeof(int));
	
	}

	neuron->inputs[neuron->numConnections] = (int *)&(input->y);
	neuron->weights[neuron->numConnections] = weight;
	neuron->numConnections++;
		

}



void transferFunction(Neuron *neuron, float threshold)
{
	int i;
	int y_in=0;

	for(i=0;i<neuron->numConnections;i++)
		y_in+= *neuron->inputs[i] * neuron->weights[i];

	printf("Y_IN %d THRESHOLD %.3f\n",y_in,threshold);
	if(y_in>=threshold)
		neuron->y = 1;
	else
		neuron->y = 0;

}


