
#ifndef AUTOENCODER_H
#define AUTOENCODER_H


#include "backpropagation.h"


void construye_bd_autoencoder(int n, FILE *output);

int learnBackPropagationAutoencoder(float **weightsV, float **weightsW, float *bias, Pattern *pattern, 
	int numHiddenLayerNeurons, float learnRate, int numPatterns, FILE *output);

int testBackPropagationAutoencoder(float **weightsV, float **weightsW, float *bias, Pattern *pattern, 
	int numHiddenLayerNeurons, float learnRate, int numFirstPattern, FILE *output);

#endif