
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
	int id;
	int **inputs;
	int *weights;
	int numConnections;

}Neuron;

typedef struct {

	Neuron inputs[3];
	Neuron outputNeurons[2];
	Neuron fstHiddenLayer[3];
	Neuron scndHiddenLayer[6];
	float threshold;

}Network;

int parserBasic(FILE *inputFile, boolean *x1, boolean *x2, boolean *x3);

void initNeuron(Neuron *neuron, int id);
void freeNeuron(Neuron *neuron);

void addConnection(Neuron *neuron, Neuron *input, int weight);
void transferFunction(Neuron *neuron, float threshold);

void initNetworkMP(Network *net, float threshold);
void freeNetworkMP(Network *net);
int getOutputNetworkMP(Network *net, int n_neuron);

void feedNetworkMP(Network *net, int x1, int x2, int x3);
void propagateMP(Network *net);

#endif