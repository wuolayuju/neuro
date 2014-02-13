
#ifndef PERCEPTRON_H
#define PERCEPTRON_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE 256
#define NUM_MAX_ITER 3000
#define INCR_SIZE_PATTERN 100

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

typedef struct
{
	float **attributes;
	int **categories;
	int numAttributes;
	int numCategories;
	int numPatterns;
}Pattern;

int parser(FILE *file, Pattern *pattern);

void freePattern(Pattern *pattern);

void initNeuron(Neuron *neuron, int id, int numConnections);
void freeNeuron(Neuron *neuron);
void createPerceptron(Perceptron *p, float threshold, int numConnections, int numOutputs);
void deletePerceptron(Perceptron *p);


int learn(Perceptron *perceptron, float learningRate, float threshold, FILE *file, int endFile);
int test(Perceptron *perceptron, FILE *file, int endFile);


#endif