
#ifndef BACKPROPAGATION_H
#define BACKPROPAGATION_H

#include "perceptron.h"
#include <limits.h>


void initWeights(float **weights, int numHidderLayerNeurons, int numAtributtes);
void nguyenWidrow(float **weights, int weightsRow, int weightsColumn, 
	float *bias, int numHiddenLayerNeurons, int numInputs);

float **generateWeights(int weightsRow, int weightsColumn);
float *generateBias(int numHidderLayerNeurons, int numCategories);
void freeWeights(float **weights, int weightsRow);

float function_binary(float in);
float function_bipolar(float in);
float dfunction_bipolar(float fx);
float dfunction_binary(float fx);

void patternNormalization(Pattern *patterns, int numPatterns);

int learnBackPropagation(float **weightsV, float **weightsW, float *bias, Pattern *pattern, 
	int numHiddenLayerNeurons, float learnRate, int numPatterns, FILE *output);
int testBackPropagation(float **weightsV, float **weightsW, float *bias, Pattern *pattern, 
	int numHiddenLayerNeurons, float learnRate, int numFirstPattern, FILE *output);

void debugWeight(float **weight, int row, int column);
int exploit(float **weightsV, float **weightsW, float *bias, Pattern *pattern, 
	int numHiddenLayerNeurons, float learnRate, FILE *output);
#endif