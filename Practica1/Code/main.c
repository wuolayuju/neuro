

#include "mccullochPitts.h"


int main(void)
{
	/*boolean x1,x2,x3;*/
	/*FILE *input=fopen("input","r");
	boolean inputs[256][3];
		Neuron neuron;
	Neuron n1,n2;
	int i;
	int times;
	int y_in=0;*/
/*
	while(parser(input,&x1,&x2,&x3)!=ERROR)
	{
		printf("OJETE %d %d %d\n",x1,x2,x3);

	}

	times = parser(input,inputs);

	for(i=0;i<times;i++)
		printf("RICO %d %d %d\n",inputs[i][0],inputs[i][1],inputs[i][2]);



	n1.y=1;
	n2.y=1;

	neuron.inputs = (int **)malloc(sizeof(int)*2);
	neuron.weights = (int *)malloc(sizeof(int)*2);
	neuron.numConnections=2;
	neuron.inputs[0]=&n1.y;
	neuron.inputs[1]=&n2.y;
	neuron.weights[0]=2;
	neuron.weights[1]=5;
	n2.y=0;

	initNeuron(&neuron);
	addConnection(&neuron,&n2,6);
	addConnection(&neuron,&n1,2);


	transferFunction(&neuron,4);
	printf("AYAYAY %d\n",neuron.y);

	n2.y=0;

	transferFunction(&neuron,4);
	printf("AYAYAY %d\n",neuron.y);

	freeNeuron(&neuron);
	*/

/*
	NetworkXOR network;

	initNetworkXOR(&network,1,0,2);

	transferFunction(&network.fstHiddenLayer[0],network.threshold);
	transferFunction(&network.fstHiddenLayer[1],network.threshold);

	transferFunction(&network.outputNeuron,network.threshold);
	
	freeNetworkXOR(&network);

	NetworkXOREpochs netxor;

	initNetworkXOREpochs(&netxor);
	printf("0 0\n");
	feedNetworkXOREpochs(&netxor, 0, 0);
	printf("0 1\n");
	feedNetworkXOREpochs(&netxor, 0, 1);
	printf("1 0\n");
	feedNetworkXOREpochs(&netxor, 1, 0);
	printf("1 1\n");
	feedNetworkXOREpochs(&netxor, 1, 1);
	printf("0 0\n");
	feedNetworkXOREpochs(&netxor, 0, 0);
	printf("0 0\n");
	feedNetworkXOREpochs(&netxor, 0, 0);

	freeNetworkXOREpochs(&netxor);
*/
	Network net;

	initNetworkMP(&net,2);
	feedNetworkMP(&net, 1, 0, 0);
	feedNetworkMP(&net, 0, 1, 0);
	feedNetworkMP(&net, 0, 0, 1);
	feedNetworkMP(&net, 1, 0, 0);
	printf("FINALLL O1 %d O2 %d\n",net.outputNeurons[0].y,net.outputNeurons[1].y);

	feedNetworkMP(&net, 0, 0, 1);
	feedNetworkMP(&net, 0, 1, 0);
	feedNetworkMP(&net, 1, 0, 0);
	printf("FINALLL O1 %d O2 %d\n",net.outputNeurons[0].y,net.outputNeurons[1].y);

	feedNetworkMP(&net, 0, 0, 1);
	feedNetworkMP(&net, 0, 1, 0);
	feedNetworkMP(&net, 1, 0, 0);
	printf("FINALLL O1 %d O2 %d\n",net.outputNeurons[0].y,net.outputNeurons[1].y);

	feedNetworkMP(&net, 1, 0, 0);
	feedNetworkMP(&net, 0, 1, 0);
	feedNetworkMP(&net, 0, 0, 1);
	//feedNetworkMP(&net, 1, 0, 0);
	printf("FINALLL O1 %d O2 %d\n",net.outputNeurons[0].y,net.outputNeurons[1].y);

	freeNetworkMP(&net);
	return 0;

}