
#ifndef MCCULLOCHPITTS_H
#define MCCULLOCHPITTS_H

#include <stdio.h>
#include <stdlib.h>

#define MAX_LINE 256

typedef enum
{
	true=1,
	false=0
}boolean;


typedef struct
{
	boolean y;
	int **inputs;
	int *weights;
	int numConnections;

}Neuron;

typedef struct {

	Neuron outputNeurons[2];
	Neuron fstHiddenLayer[3];
	Neuron scndHiddenLayer[6];

}Network;

int parserBasic(FILE *inputFile, boolean *x1, boolean *x2, boolean *x3);
int parser(FILE *inputFile,boolean inputs[][3]);

void initNeuron(Neuron *neuron);
void freeNeuron(Neuron *neuron);

void addConnection(Neuron *neuron, Neuron *input, int weight);
void transferFunction(Neuron *neuron, float threshold);

void initNetworkMP(Network *net, int x1, int x2, int x3);
void freeNetworkMP(Network *net);

#endif