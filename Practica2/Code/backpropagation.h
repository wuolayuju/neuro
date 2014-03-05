
#ifndef BACKPROPAGATION_H
#define BACKPROPAGATION_H

#include "perceptron.h"


float **generateWeightsV();
float **generateWeightsW();


void initBias();
void initWeights(float **weights, int numHidderLayerNeurons, int numAtributtes);

float **generateWeights(int weightsRow, int weightsColumn);
float *generateBias(int numHidderLayerNeurons, int numCategories);

float function_binary(float in);
float function_bipolar(float in);
float dfunction_bipolar(float fx);
float dfunction_binary(float fx);

int learnBackPropagation(float **weightsV, float **weightsW, float *bias, Pattern *pattern, 
	int numHidderLayerNeurons, float learningRate, int numPatterns);

#endif