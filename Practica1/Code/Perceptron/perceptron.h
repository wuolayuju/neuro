
#ifndef PERCEPTRON_H
#define PERCEPTRON_H

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
	int y;
	int id;
	int **inputs;
	int *weights;
	int numConnections;
}Neuron;

typedef struct
{
	float threshold;
	int *inputs;
	int numInputs;
	Neuron *outputs;
	int numOutputs;

}Perceptron;



int learn(Perceptron *perceptron, float learningRate, float threshold, FILE *file, int endFile);
int test(Perceptron *perceptron, FILE *file, int endFile);
void createPerceptron(Perceptron *p, int numConnections, int numOutputs);
void deletePerceptron(Perceptron *p);

#endif