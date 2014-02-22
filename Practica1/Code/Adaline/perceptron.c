
#include "perceptron.h"


/***************************************************/
/* Funcion: aleat_num Fecha: 29/09/2012            */
/* Autores: Adrián Lorenzo Mateo                   */
/*        Ari Handler Gamboa               */
/*                                                 */
/* Rutina que genera un numero aleatorio           */
/* entre dos numeros dados                         */
/*                                                 */
/* Entrada:                                        */
/* int inf: limite inferior                        */
/* int sup: limite superior                        */
/* Salida:                                         */
/* int: numero aleatorio                           */
/***************************************************/
int getRandomNumber(int inf, int sup)
{
    /* Control de errores de los parametros de entrada*/
    if ((sup < inf) || (sup > RAND_MAX) || ((inf < 0 ) ||
            (sup < 0)) || (sup > RAND_MAX))
        return -1;
    /*la función rand() limita el rango [0, 1) debido a la división entre RAND_MAX+1.
     * La segunda parte multiplica dicho valor por un número que se encuentre aproximadamente
     * en la mitad del rango (sup-inf +1), de este modo se normaliza el anterior valor
     * acotándolo entre 0 y el número intermedio.  Sin embargo, es necesario sumar el límite
     * inferior al resultado con el fin de que se obtenga un valor superior a este.*/
    return (int)((rand()/(RAND_MAX+1.))*(sup-inf+1))+inf;
}

int swap(int pos_1, int pos_2, void **vector)
{

    void *ptr = NULL;
    if((vector == NULL) || ((pos_1 < 0) || (pos_2 < 0)))
        return 0;

    ptr = vector[pos_1];
    vector[pos_1] = vector[pos_2];
    vector[pos_2] = ptr;

    return 1;

}

int patternShuffle(Pattern *p, int seed)
{
    int indice;
    int i;

    srand(seed);
    
    for (i=0; i< p->numPatterns ;i++)
    {
    	indice = getRandomNumber(i,p->numPatterns-1);
        swap(i,indice,(void **)p->categories);
        swap(i,indice,(void **)p->attributes);   	
    }



    return 1;
}

void initNeuron(Neuron *neuron, int id, int numConnections)
{
	neuron->id = id;
	neuron->weights = (float *)calloc(sizeof(float),numConnections);
	neuron->inputs = (float *)malloc(sizeof(float)*numConnections);
	neuron->y = 0;
	neuron->b = 0;
	neuron->numConnections = numConnections;
}

void freeNeuron(Neuron *neuron)
{
	if(neuron->inputs!=NULL)
	{
		free(neuron->weights);
		free(neuron->inputs);
		neuron->weights = NULL;
		neuron->inputs = NULL;
		neuron->numConnections = 0;
	}
}



void createPerceptron(Perceptron *p, float threshold, int numConnections, int numOutputs)
{
	//int i;

	p->threshold = threshold;
	p->numOutputs = numOutputs;

	p->inputs = (float *)malloc(sizeof(float)*numConnections);
	p->numInputs = numConnections;
	//p->outputs = (Neuron *)malloc(sizeof(Neuron)*numOutputs);
	//for(i=0;i<numOutputs;i++)
	//{
	initNeuron(&p->output,0,numConnections);
	//}


}

void deletePerceptron(Perceptron *p)
{

	freeNeuron(&p->output);
	free(p->inputs);
		
}


void transferFunction(Neuron *neuron, float threshold)
{

	int i;
	float y_in=0;


	for(i=0;i<neuron->numConnections;i++){
		y_in += neuron->inputs[i] * neuron->weights[i];
	}

	y_in += neuron->b;

	if(y_in > threshold)
		neuron->y = 1;
	else if(y_in < -threshold)
		neuron->y = -1;
	else
		neuron->y = 0;

	if(DEBUG_TEST)
		printf("Y_IN = %.2f Y = %d\n", y_in, neuron->y);
}

int parser(FILE *file, Pattern *pattern)
{
	int numAttributes, numCategories;
	char string[MAX_LINE];
	char tokens[ ] = " \n\t";
	char *ptr = NULL;
	int patternCount=0;
	int i;

	// Lectura del numero de atributos y clases del fichero
	fscanf(file, "%d %d\n", &numAttributes, &numCategories);
	if(numAttributes<=0 || numCategories<=0)
		return 0;

	// Reserva de memoria inicial para almacenar los patrones
	pattern->attributes = (float **)malloc(sizeof(float *)*INCR_SIZE_PATTERN);
	pattern->categories = (int **)malloc(sizeof(int *)*INCR_SIZE_PATTERN);

	for(i=0;i<INCR_SIZE_PATTERN;i++)
	{
		pattern->attributes[i]= (float *)malloc(sizeof(float)*numAttributes);
		pattern->categories[i]= (int *)malloc(sizeof(int)*numCategories);
	}
	
	while(fgets(string,MAX_LINE,file)!=NULL)
	{
		// Tokenizacion de los patrones
		ptr = strtok(string, tokens );
		pattern->attributes[patternCount][0] = atof(ptr); // Primera lectura especial

		for(i=1;i<numAttributes;i++)
		{
			ptr = strtok(NULL, tokens );
			pattern->attributes[patternCount][i] =atof(ptr);
		}

		for(i=0;i<numCategories;i++)
		{
			ptr = strtok(NULL, tokens );
			pattern->categories[patternCount][i] =  atoi(ptr);	
		}

		// Aumento de la memoria reservada para los patrones en caso necesario
		patternCount++;
		if ((patternCount % INCR_SIZE_PATTERN) == 0)
		{		
			pattern->attributes = (float **)realloc(pattern->attributes, sizeof(float *)*(INCR_SIZE_PATTERN+patternCount));
			pattern->categories = (int **)realloc(pattern->categories, sizeof(int *)*(INCR_SIZE_PATTERN+patternCount));

			for(i=patternCount; i < INCR_SIZE_PATTERN+patternCount ; i++)
			{
				pattern->attributes[i]= (float *)malloc(sizeof(float)*numAttributes);
				pattern->categories[i]= (int *)malloc(sizeof(int)*numCategories);
			}
		}
	}

	pattern->numAttributes = numAttributes;
	pattern->numCategories = numCategories;
	pattern->numPatterns = patternCount;

	return 1;
}

int createPattern(FILE *file, Pattern *p)
{
	if(parser(file, p))
	{
		patternShuffle(p, time(NULL));
		return 1;
	}
	return 0;
}

void freePattern(Pattern *pattern)
{
	int i;

	// Hay que liberar hasta un total del techo a centenas de numPatterns
	int totalToFree = 100 - (pattern->numPatterns % 100) + pattern->numPatterns;

	for (i = 0; i < totalToFree ;i++)
	{
		free(pattern->attributes[i]);
		free(pattern->categories[i]);
	}
	free(pattern->attributes);
	free(pattern->categories);

}

int learnPerceptron(
	Perceptron *perceptron, float learningRate, 
	float threshold, Pattern *patterns, 
	int numberPatterns)
{
	int p, i, w;
	boolean weightChange=false;
	boolean weightChangeEpoch=false;
	int n_iter = 1;
	int currentCategory;
	int errors = 0;

	do{

		errors = 0;

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

			// Aplicación de la función de transferencia
			transferFunction(&perceptron->output, perceptron->threshold);

			// Conversión de categoria original a la necesaria para learn
			if (patterns->categories[p][0] == 1)
				currentCategory = 1;
			else
				currentCategory = -1;

			if(DEBUG_TEST)
				printf("T = %d\n", currentCategory);
			
			// Comprobación de error
			if ((perceptron->output.y != currentCategory) || (perceptron->output.y == 0))
			{
				weightChange = true;
				weightChangeEpoch = true;
				errors++;
			}

			else
				weightChange = false;

			// Cambio en los pesos
			if (weightChange == true) {
				for (w = 0; w < perceptron->numInputs; w++)
				{
					perceptron->output.weights[w] += learningRate * patterns->attributes[p][w] * currentCategory;
					if(DEBUG_TEST)
						printf("DELTA peso %d  %.2f\n",w,learningRate * patterns->attributes[p][w] * currentCategory);
				}
				perceptron->output.b += learningRate * currentCategory;
				if(DEBUG_TEST)
					printf("\n");
			}
			if(DEBUG_TEST)
			{
				for(i=0;i<perceptron->output.numConnections;i++)
					printf("W %.2f ",perceptron->output.weights[i]);
				printf("\n");
			}
      	}
      	n_iter++;
      	if (n_iter > NUM_MAX_ITER)
      		break;

      	printf("ERRORES = %.4f\n",(float)errors/numberPatterns*100);

	}while (weightChangeEpoch);

	return 0;

}

int printTest(Perceptron *perceptron, Pattern *pattern, int numFirstPattern, FILE *out)
{

	int i, j;

	
	for(i=numFirstPattern; i<pattern->numPatterns ;i++)
	{
		if(DEBUG_TEST)
			printf("Entrada: ");
		for (j = 0; j < perceptron->numInputs ; j++)
		{
			perceptron->output.inputs[j] = pattern->attributes[i][j];
			if(DEBUG_TEST)
				printf("%.1f ", perceptron->output.inputs[j]);
		}
		if(DEBUG_TEST)
			printf("\n");

		transferFunction(&perceptron->output, perceptron->threshold);

		if(perceptron->output.y == 1)
			fprintf(out,"0 1\n");

		else if(perceptron->output.y == -1)
			fprintf(out,"1 0\n");
		else
			fprintf(out,"0 0\n");
	}
	return 1;
}

int test(Perceptron *perceptron, Pattern *pattern, int numFirstPattern)
{
	int i, j;
	int currentCategory;
	int hits = 0;
	int totalTargetCat_1 = 0; /* Cateogoria 1 */
	int totalTargetCat_2 = 0; /* Cateogoria 1 */
	int totalTestCat_1 = 0; /* Cateogoria 1 */
	int totalTestCat_2 = 0; /* Cateogoria -1 */
	int nTestPatterns = 0;
	int errors = 0;

	for(i=numFirstPattern; i<pattern->numPatterns ;i++)
	{
		if(DEBUG_TEST)
			printf("Entrada: ");
		for (j = 0; j < perceptron->numInputs ; j++)
		{
			perceptron->output.inputs[j] = pattern->attributes[i][j];
			if(DEBUG_TEST)
				printf("%.1f ", perceptron->output.inputs[j]);
		}
		if(DEBUG_TEST)
			printf("\n");

		transferFunction(&perceptron->output, perceptron->threshold);

		if (pattern->categories[i][0] == 1){
			currentCategory = 1;
			totalTargetCat_1++;
		}
		else{
			currentCategory = -1;
		}
		if (DEBUG_TEST)
			printf("T = %d\n", currentCategory);

		if (perceptron->output.y == currentCategory)
			hits++;

		if (perceptron->output.y == 1)
			totalTestCat_1++;
		else if (perceptron->output.y == -1)
			totalTestCat_2++;
	}

	nTestPatterns = pattern->numPatterns - numFirstPattern;

	errors = nTestPatterns - hits;

	totalTargetCat_2 = nTestPatterns - totalTargetCat_1;

	printf("\nClase 1 = %d (%.2f%%)\n", totalTargetCat_1, (float)totalTargetCat_1/nTestPatterns*100);
	printf("Clase 2 = %d (%.2f%%)\n", totalTargetCat_2, (float)totalTargetCat_2/nTestPatterns*100);

	printf("\nFallos = %d (%.2f%%)\n", errors, (float)errors/nTestPatterns*100);
	printf("Aciertos = %d (%.2f%%)\n", hits, (float)hits/nTestPatterns*100);


	return 1;
}