
#include "perceptron.h"

void initNeuron(Neuron *neuron, int id, int numConnections)
{
	neuron->id = id;
	neuron->weights = (int *)calloc(sizeof(int),numConnections);
	neuron->inputs = (int **)malloc(sizeof(int *)*numConnections);
	neuron->y = 0;
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
	int i;

	p->threshold = threshold;
	p->numOutputs = numOutputs;

	p->inputs = (int *)malloc(sizeof(int)*numConnections);
	p->outputs = (Neuron *)malloc(sizeof(Neuron)*numOutputs);
	for(i=0;i<numOutputs;i++)
	{
		initNeuron(&p->outputs[i],i,numConnections);
	}
}

void deletePerceptron(Perceptron *p)
{
	int i;

	for(i=0;i<p->numOutputs;i++)
	{
		freeNeuron(&p->outputs[i]);
	}
	free(p->outputs);
	free(p->inputs);
		
}


void transferFunction(Neuron *neuron, float threshold)
{

	int i;
	int y_in=0;

	for(i=0;i<neuron->numConnections;i++)
		y_in+= *neuron->inputs[i] * neuron->weights[i];

	if(y_in>threshold)
		neuron->y = 1;
	else if(y_in<-threshold)
		neuron->y = -1;
	else
		neuron->y = 0;
}

int parser(FILE *file, Pattern *pattern)
{
	int numAttributes, numCategories;
	int numIncr = 1;
	char string[MAX_LINE];
	char tokens[ ] = " \n\t";
	char *ptr = NULL;
	int patternCount=0;
	int i;

	fscanf(file, "%d %d\n", &numAttributes, &numCategories);

	if(numAttributes<=0 || numCategories<=0)
		return 0;

	printf("NA = %d, NC = %d\n", numAttributes, numCategories);
	pattern->attributes = (float **)malloc(sizeof(float)*INCR_SIZE_PATTERN);
	pattern->categories = (int **)malloc(sizeof(int)*INCR_SIZE_PATTERN);

	printf("DONE MALLOC INIT\n");

	for(i=0;i<INCR_SIZE_PATTERN;i++)
	{
		pattern->attributes[i]= (float *)malloc(sizeof(float)*numAttributes);
		pattern->categories[i]= (int *)malloc(sizeof(int)*numCategories);
	}

	printf("DONE MALLOC TOTO\n");
	
	while(fgets(string,MAX_LINE,file)!=NULL)
	{
		printf("OLINGUI %s\n",string);
		// Tokenizacion de los patrones
		ptr = strtok(string, tokens );
		if(ptr == NULL)
			printf("MECAGOENLAHOSTIA\n");
		printf("%s ", ptr);
		pattern->attributes[patternCount][0] = atof(ptr);
		for(i=1;i<numAttributes;i++)
		{
			ptr = strtok(NULL, tokens );
			pattern->attributes[patternCount][i] =atof(ptr);
			printf("%s ", ptr);
		}
		for(i=0;i<numCategories;i++)
		{
			ptr = strtok(NULL, tokens );
			pattern->categories[patternCount][i] =  atoi(ptr);	
			printf("%s ", ptr);		
		}
		printf("\n");
		patternCount++;
		printf("PATTER %d\n",patternCount);
		// Aumento de la memoria reservada para los patrones en caso necesario
		if ((patternCount % INCR_SIZE_PATTERN) == 0)
		{
			//printf("ROQUEFOR %d\n",patternCount);
			
			pattern->attributes = (float **)realloc(pattern->attributes, sizeof(float)*(INCR_SIZE_PATTERN)*numIncr);
			pattern->categories = (int **)realloc(pattern->categories, sizeof(int)*(INCR_SIZE_PATTERN)*numIncr);
			if(patternCount == 200)
				break;
			for(i=patternCount; i < INCR_SIZE_PATTERN+patternCount ; i++)
			{
				pattern->attributes[i]= (float *)malloc(sizeof(float)*numAttributes);
				pattern->categories[i]= (int *)malloc(sizeof(int)*numCategories);
			}
			//numIncr++;
		}
	}

	pattern->numAttributes = numAttributes;
	pattern->numCategories = numCategories;
	pattern->numPatterns = patternCount;

	return 1;
}

void freePattern(Pattern *pattern)
{
	int i;

	for (i = 0; i < pattern->numPatterns;i++)
	{
		free(pattern[i].attributes);
		free(pattern[i].categories);
	}
	free(pattern->attributes);
	free(pattern->categories);
}

int learn(Perceptron *perceptron, float learningRate, float threshold, FILE *file, int endFile)
{
	int numConnections, numOutputs;
	long filePosition;
	int p, i, w, patternCount=0;
	int index=0;
	int **y = NULL;
	int **x = NULL;
	char ch;
	char string[MAX_LINE];
	boolean weightChange=false;
	char *ptr;
	char token[ ] = " \n\t";

	fscanf(file, "%d %d\n", &numConnections, &numOutputs);
	createPerceptron(perceptron, threshold, numConnections, numOutputs);

	filePosition = ftell(file);

	/*obtiene el numero de patrones*/
	do 
	{
	    ch = fgetc(file);
	    if(ch == '\n')
	    	patternCount++;
	} while (ch != EOF);


	// last line doesn't end with a new line!
	// but there has to be a line at least before the last line
	if(ch != '\n' && patternCount != 0) 
	    patternCount++;

	y = (int **)malloc(sizeof(int *) * patternCount);
	x = (int **)malloc(sizeof(int *) * patternCount);

	for(i=0;i<patternCount;i++)
	{
		y[i] = (int *)malloc(sizeof(int) * numOutputs);
		x[i] = (int *)malloc(sizeof(int) * numConnections);
	}

	/*vuelve donde estaba en el fichero*/
	fseek(file,filePosition,SEEK_SET);

	while( index<endFile && (fgets(string,MAX_LINE,file)!=NULL))
	{
		ptr = strtok(string, token );

		index++;
	}


	do{
		for (p = 0; p < patternCount; p++)
		{
			for(i=0;i<numOutputs;i++)
			{
				transferFunction(&perceptron->outputs[i],perceptron->threshold);
				if(y[p][i] != perceptron->outputs[i].y)
				{
					weightChange = true;
					for(w=0;w < perceptron->outputs[w].numConnections; w++)
						perceptron->outputs[i].weights[w] += learningRate * y[p][i] * x[p][w];
				}
			}
      	}
	}while (weightChange);


	/*Memory free*/
	for(i=0;i<patternCount;i++)
	{
		free(x[i]);
		free(y[i]);
	}
	free(x);
	free(y);

	return 0;

}

int test(Perceptron *perceptron, FILE *file, int endFile)
{

	return 0;
}