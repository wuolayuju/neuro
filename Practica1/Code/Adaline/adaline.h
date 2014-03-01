
#ifndef ADALINE_H
#define ADALINE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <time.h>
#include <math.h>  
#include "perceptron.h"



int learnAdaline(Perceptron *perceptron, float learningRate, 
	float threshold, Pattern *patterns, int numberPatterns, float errorTolerance);

float getRandomNumberF(float inf, float sup);

void initWeightsAdaline(Perceptron *perceptron);
#endif