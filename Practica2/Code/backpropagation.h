
#ifndef BACKPROPAGATION_H
#define BACKPROPAGATION_H

#include "perceptron.h"


float **generateWeightsV();
float **generateWeightsW();


void initBias();
void initWeights(float **weights, int numHidderLayerNeurons, int numAtributtes);
int learnBackPropagation();

float **generateWeightsV(int numHidderLayerNeurons, int numAtributtes);
float **generateWeightsW(int numHidderLayerNeurons, int numCategories);
float *generateBias(int numHidderLayerNeurons, int numCategories);

float function_binary(float in);
float function_bipolar(float in);

int learnBackPropagation(float **weightsV, float **weightsW, float *bias, Pattern *pattern, 
	int numHidderLayerNeurons, int numPatterns);
#endif