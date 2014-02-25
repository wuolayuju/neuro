
#include "adaline.h"

float getRandomNumberF(float inf, float sup)
{
    /* Control de errores de los parametros de entrada*/
    if ((sup < inf) || (sup > RAND_MAX) || (sup < 0) || (sup > RAND_MAX))
        return -1;
    /*la función rand() limita el rango [0, 1) debido a la división entre RAND_MAX+1.
     * La segunda parte multiplica dicho valor por un número que se encuentre aproximadamente
     * en la mitad del rango (sup-inf +1), de este modo se normaliza el anterior valor
     * acotándolo entre 0 y el número intermedio.  Sin embargo, es necesario sumar el límite
     * inferior al resultado con el fin de que se obtenga un valor superior a este.*/
    return (float)((rand()/(RAND_MAX+1.))*(sup-inf))+inf;
}

void initWeightsAdaline(Perceptron *perceptron)
{
	int i;

	for(i=0; i<perceptron->output.numConnections; i++)
		perceptron->output.weights[i] = getRandomNumberF(-0.1,0.1);

	for(i=0; i<perceptron->output.numConnections; i++)
		printf("W %.3f ",perceptron->output.weights[i]);
	printf("\n");
}

int learnAdaline(
	Perceptron *perceptron, float learningRate, 
	float threshold, Pattern *patterns, 
	int numberPatterns, float errorTolerance)
{
	int p, i, w;
	boolean weightChange=false;
	boolean weightChangeEpoch=false;
	float biggerWeightChange;
	float deltaChange;
	int n_iter = 1;
	int currentCategory;
	float errors = 0;
	float y_in;

	do{

		errors = 0;

		biggerWeightChange = -1;

		if(DEBUG_TEST)
			printf("=========EPOCA %d==========\n", n_iter);

		weightChangeEpoch = false;

		for (p = 0; p < numberPatterns; p++)
		{

			if(DEBUG_TEST)
				printf("Entrada: ");
			// Estimulacion de las entradas
			for (i = 0; i < perceptron->numInputs ; i++)
			{
				perceptron->output.inputs[i] = patterns->attributes[p][i];
				if(DEBUG_TEST)
					printf("%.1f ", perceptron->output.inputs[i]);
			}
			if(DEBUG_TEST)
				printf("\n");

			y_in = 0;

			// Aplicación de la función de transferencia, en este caso la entrada neta
			for(i=0;i<perceptron->output.numConnections;i++){
				y_in += perceptron->output.inputs[i] * perceptron->output.weights[i];
			}

			y_in += perceptron->output.b;

			if(DEBUG_TEST)
				printf("Y_IN %.3f\n",y_in);
			// Conversión de categoria original a la necesaria para learn
			if (patterns->categories[p][0] == 1)
				currentCategory = 1;
			else
				currentCategory = -1;

			if(DEBUG_TEST)
				printf("T = %d\n", currentCategory);

			errors += (float)pow((currentCategory - y_in),2);

			// Cambio en los pesos
			
			for (w = 0; w < perceptron->numInputs; w++)
			{
				deltaChange = learningRate * patterns->attributes[p][w] * 
					(currentCategory - y_in);
				perceptron->output.weights[w] += deltaChange;

				if(deltaChange > biggerWeightChange)
					biggerWeightChange = deltaChange;

				if(DEBUG_TEST)
					printf("DELTA peso %d  %.2f\n",w, deltaChange);
			}
			deltaChange = learningRate * (currentCategory - y_in);
			perceptron->output.b += deltaChange;

			if(deltaChange > biggerWeightChange)
					biggerWeightChange = deltaChange;
				
			if(DEBUG_TEST)
				printf("\n");
	
			if(DEBUG_TEST)
			{
				for(i=0;i<perceptron->output.numConnections;i++)
					printf("W %.2f ",perceptron->output.weights[i]);
				printf("\n");
			}
      	}


      	printf("Epoca %d Error Cuadrático Medio :%.4f\n",
				n_iter, (float)errors/numberPatterns);
      	if(DEBUG_TEST)
      		printf("BIGGEST CHANGE %.3f ERROR TOLERANCE %.3f\n",fabs(biggerWeightChange),errorTolerance);
      	n_iter++;
      	if (n_iter > NUM_MAX_ITER)
      		break;

      	//printf("\nEPOCA %d ERRORES = %.4f\n", n_iter, (float)errors/numberPatterns*100);

	}while (fabs(biggerWeightChange) > errorTolerance);

	return 0;

}
