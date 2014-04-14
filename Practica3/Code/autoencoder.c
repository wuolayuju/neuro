

#include "autoencoder.h"


void construye_bd_autoencoder(int n, FILE *output)
{

	int i,j, k;

	fprintf(output,"%d %d\n",n*n,n*n);

	/*Patron vacío*/
	for(i=0;i<n*n;i++)
		fprintf(output,"0 ");
	for(i=0;i<n*n;i++)
		fprintf(output,"0 ");
	fprintf(output,"\n");

	/*Patrones Horizontales*/
	for(i=0;i<n;i++)
	{
		/*entradas*/
		for(j=0;j<n*n;j++)
		{
			if(j>=i*n&&j<n*(i+1))
				fprintf(output,"1 ");
			else
				fprintf(output,"0 ");
		}
		/*salidas*/
		for(j=0;j<n*n;j++)
		{
			if(j>=i*n&&j<n*(i+1))
				fprintf(output,"1 ");
			else
				fprintf(output,"0 ");
		}
		fprintf(output,"\n");
	}

	/*Patrones Verticales*/
	for(i=0;i<n;i++)
	{
		/*entradas*/
		for(j=0;j<n*n;j++)
		{
			if(j % n == i)
				fprintf(output,"1 ");
			else
				fprintf(output,"0 ");			
		}
		/*salidas*/
		for(j=0;j<n*n;j++)
		{
			if(j % n == i)
				fprintf(output,"1 ");
			else
				fprintf(output,"0 ");			
		}
		fprintf(output,"\n");
	}
	/*Combinacion de patrones Verticales*/
	for(i=0;i<n;i++)
	{
		
		for(j=1;(i+j<n);j++)
		{
			/*entradas*/
			for(k=0;k<n*n;k++)
			{
				if((k % n == i || k % n == i+j))
					fprintf(output,"1 ");
				else
				fprintf(output,"0 ");
			}
			/*salidas*/
			for(k=0;k<n*n;k++)
			{
				if((k % n == i || k % n == i+j))
					fprintf(output,"1 ");
				else
				fprintf(output,"0 ");
			}
			fprintf(output,"\n");
		}
	
	}

	/*Combinacion de patrones Horizontales*/
	for(i=0;i<n;i++)
	{
		
		for(j=1;(i+j<n);j++)
		{
			/*entradas*/
			for(k=0;k<n*n;k++)
			{
				if((k>=i*n&&k<n*(i+1)) || (k>=(i+j)*n&&k<n*((i+j)+1)))
					fprintf(output,"1 ");
				else
				fprintf(output,"0 ");
			}
			/*salidas*/
			for(k=0;k<n*n;k++)
			{
				if((k>=i*n&&k<n*(i+1)) || (k>=(i+j)*n&&k<n*((i+j)+1)))
					fprintf(output,"1 ");
				else
				fprintf(output,"0 ");
			}
			fprintf(output,"\n");
		}
	
	}


	/*Combinacion de patrones Vert/Horiz*/
	for(i=0;i<n;i++)
	{
		for(j=0;j<n;j++)
		{
			/*entradas*/
			for(k=0;k<n*n;k++)
			{
				if((k>=j*n&&k<n*(j+1)) || k % n == i)
					fprintf(output,"1 ");
				else 
					fprintf(output,"0 ");
			}
			/*salidas*/
			for(k=0;k<n*n;k++)
			{
				if((k>=j*n&&k<n*(j+1)) || k % n == i)
					fprintf(output,"1 ");
				else 
					fprintf(output,"0 ");
			}
			fprintf(output,"\n");
		}
	}

}

/******************************************************************************
Purpose:

	Calculates the value of bipolar sigmoidal derived function

Author:

	Ari Handler Adrián Lorenzo

Parameters:

	weightsV
	weightsW
	bias
	pattern 
	numHiddenLayerNeurons
	learnRate
	numPatterns

******************************************************************************/
int learnBackPropagationAutoencoder(float **weightsV, float **weightsW, float *bias, Pattern *pattern, 
	int numHiddenLayerNeurons, float learnRate, int numPatterns, FILE *output)
{

	int i, j, p;

	float *y_in = NULL;
	float *z_in = NULL;
	float *z = NULL;
	float *y = NULL;

	float *dk = NULL;

	float *d_inj = NULL;
	float *dj = NULL;

	float **Av = NULL;
	float **Aw = NULL;
	float *Ab = NULL;

	int n_iter = 0;
	float RMS;
	int hits;
	/**ALLOC BLOCK**/
	
	/*Neuron Inputs*/
	z_in = (float *)calloc(sizeof(float),numHiddenLayerNeurons);
	y_in = (float *)calloc(sizeof(float),pattern->numCategories);

	/*Neuron Outputs*/
	z = (float *)calloc(sizeof(float),numHiddenLayerNeurons);
	y = (float *)calloc(sizeof(float),pattern->numCategories);

	/*Errores*/
	dk = (float *)malloc(sizeof(float)*pattern->numCategories);
	d_inj = (float *)calloc(sizeof(float),numHiddenLayerNeurons);
	dj = (float *)malloc(sizeof(float)*numHiddenLayerNeurons);

	

	/*Incrementos de peso*/
	Aw = (float **)malloc(sizeof(float *)*pattern->numCategories);
	for(i=0;i<pattern->numCategories;i++)
		Aw[i] = (float *)malloc(sizeof(float)*numHiddenLayerNeurons);

	Av = (float **)malloc(sizeof(float *)*numHiddenLayerNeurons);
	for(i=0;i<numHiddenLayerNeurons;i++)
		Av[i] = (float *)malloc(sizeof(float)*pattern->numAttributes);

	Ab = (float *)malloc(sizeof(float)*(numHiddenLayerNeurons + pattern->numCategories));

	/**LEARN BLOCK**/
	do
	{
		RMS = 0;
		hits = 0;
		for(p=0; p < numPatterns; p++)
		{
			if(0)
			{
				printf("%d:",p);
				for (i=0; i<pattern->numCategories; i++)
				{
					printf("%.1f ",pattern->categories[p][i]);

				}
			
				printf("| ");
			}
			/*Propagación palante*/
			for (i=0; i<numHiddenLayerNeurons; i++)
			{
				z_in[i] = bias[i];
				for (j=0; j<pattern->numAttributes; j++)
				{

					z_in[i] += weightsV[i][j] * pattern->attributes[p][j];
				}
					
				
				z[i] = (2/(1+exp(-z_in[i])))-1;

				if(0)
				{
					printf("%.2f ",z[i]);
					//printf("ZIN[%d] = %.6f\n",i,z_in[i]);
				}
					
			}
			if(0)
			{
				printf("\n");
			}
			for (i=0; i<pattern->numCategories; i++)
			{
				y_in[i] = bias[numHiddenLayerNeurons+i];
				
				for (j=0; j<numHiddenLayerNeurons; j++)
					y_in[i] += weightsW[i][j]*z[j];
				
				if(DEBUG_TEST)
					printf("Y_IN %.2f\n",y_in[i]);
				y[i] = (2/(1+exp(-y_in[i])))-1;
			
				if(!(((y[i] > 0) && (pattern->categories[p][i] > 0))
				|| ((y[i] <= 0) && (pattern->categories[p][i] < 0))))
				{	
					hits++;
				}
				if(DEBUG_TEST)
				{
					printf("Y[%d] = %.10f\n",i,y[i]);
					printf("T[%d] = %.10f\n",i,pattern->categories[p][i]);
				}
				
			}

			// Calculo y propagación del error en neuronas de salida
			// y del incremento de los pesos
			for(i=0;i<pattern->numCategories;i++)
			{
				dk[i] = (pattern->categories[p][i] - y[i])*0.5*(1 + y[i])*(1 - y[i]);
				if(DEBUG_TEST)
					printf("%.2f %.2f %.2f\n",pattern->attributes[p][i],y[i],
					0.5*(1 + z[i])*(1 - z[i]));
				if(DEBUG_TEST)
					printf("DK[%d] = %.2f\n",i,dk[i]);

				for(j=0;j<numHiddenLayerNeurons;j++)
				{
					Aw[i][j] = learnRate*dk[i]*z[j];
					if(DEBUG_TEST)
						printf("Aw[%d][%d] = %.2f\n",i,j,Aw[i][j]);
				}
				Ab[numHiddenLayerNeurons+i] = learnRate*dk[i];

				if(DEBUG_TEST)
					printf("Ab[%d] = %.2f\n",numHiddenLayerNeurons+i,
					Ab[numHiddenLayerNeurons+i]);
			}

			for (i=0; i<numHiddenLayerNeurons; i++){

				d_inj[i] = 0;

				for (j=0; j<pattern->numCategories; j++)
				{
					d_inj[i]+=dk[j]*weightsW[j][i];
					if(DEBUG_TEST)
						printf("%.3f %.3f\n",dk[j],weightsW[j][i]);
					if(DEBUG_TEST)
						printf("D_IN[%d] = %.3f\n",i,d_inj[i]);
				}

				dj[i] = d_inj[i]*0.5*(1 + z[i])*(1 - z[i]);
				if(DEBUG_TEST)
				{
					printf("DFUNCTIONBIPOLAR = %.3f\n",0.5*(1 + z[i])*(1 - z[i]));
					printf("D_J[%d] = %.3f\n",i,dj[i]);
				}
					

				for (j=0; j<pattern->numAttributes; j++)
				{
					Av[i][j]=learnRate*dj[i]*pattern->attributes[p][j];
					if(DEBUG_TEST)
						printf("Av[%d][%d] = %.3f\n",i,j,Av[i][j]);
				}
				Ab[i]=learnRate*dj[i];

				if(DEBUG_TEST)
					printf("Ab[%d] = %.3f\n",i,Ab[i]);
			}

			//Actualiza de los pesos
			for (i=0; i<pattern->numCategories; i++)
			{
				for (j=0; j<numHiddenLayerNeurons; j++)
				{
					if(DEBUG_TEST)
						printf("BEFORE w[%d][%d] = %.4f\n",i,j,weightsW[i][j]);
					weightsW[i][j] += Aw[i][j];
					if(DEBUG_TEST)
						printf("AFTER w[%d][%d] = %.4f\n",i,j,weightsW[i][j]);
				}
			}	
			for (i=0; i<numHiddenLayerNeurons; i++)
			{
				for (j=0; j<pattern->numAttributes; j++)
				{
					if(DEBUG_TEST)
						printf("BEFORE v[%d][%d] = %.4f\n",i,j,weightsV[i][j]);
					weightsV[i][j] += Av[i][j];
					if(DEBUG_TEST)
						printf("AFTER v[%d][%d] = %.4f\n",i,j,weightsV[i][j]);
				}
			}
			for (i=0;i<numHiddenLayerNeurons+pattern->numCategories;i++)
			{
				if(DEBUG_TEST)
					printf("BEFORE b[%d] = %.4f\n",i,bias[i]);
				bias[i]+=Ab[i];
				if(DEBUG_TEST)
					printf("AFTER b[%d] = %.4f\n",i,bias[i]);
			}

			for(i=0;i<pattern->numCategories;i++)
			{
				RMS += ((pow(pattern->categories[p][i] - y[i], 2))/numPatterns);
			}
				
			
		}
		n_iter++;
		fprintf(output,"Epoca %d | RMS %.5f\n",n_iter, RMS);
	
		if(0)
		{
			/*
			fprintf(output,"WEIGHTS W:\n");
			for (i=0; i<pattern->numCategories; i++)
			{
				for (j=0; j<numHiddenLayerNeurons; j++)
				{
					fprintf(output,"%.3f ",weightsW[i][j]);
				}
				fprintf(output,"\n");
			}*/
			fprintf(output,"WEIGHTS V:\n");
			for (i=0; i<numHiddenLayerNeurons; i++)
			{
				fprintf(output,"%d: ",i);
				for (j=0; j<pattern->numAttributes; j++)
				{
					fprintf(output,"%.3f ",weightsV[i][j]);
				}
				fprintf(output,"\n");
			}
			/*fprintf(output,"BIAS\n");
			for (i=0;i<numHiddenLayerNeurons+pattern->numCategories;i++)
			{
				fprintf(output,"%.4f ",bias[i]);
			}
			fprintf(output,"\n");*/
		}
		
		
		printf("Epoca %d | Pixeles fallados = %d %.0f%%\n",n_iter,hits/pattern->numCategories,
			(float)hits/pattern->numCategories/numPatterns*100);

	}while(n_iter<NUM_MAX_ITER);


	/**FREE BLOCK**/
	free(y);
	free(z);
	free(z_in);
	free(y_in);
	free(dk);
	free(Ab);

	for(i=0;i<pattern->numCategories;i++)
		free(Aw[i]);
	free(Aw);

	for(i=0;i<numHiddenLayerNeurons;i++)
		free(Av[i]);
	free(Av);

	return 1;
}

int testBackPropagationAutoencoder(float **weightsV, float **weightsW, float *bias, Pattern *pattern, 
	int numHiddenLayerNeurons, float learnRate, int numFirstPattern, FILE *output)
{
	int p,i,j;
	float *y_in = NULL;
	float *z_in = NULL;
	float *z = NULL;
	float *y = NULL;
	int hits =0;
	
	/*Neuron Inputs*/
	z_in = (float *)calloc(sizeof(float),numHiddenLayerNeurons);
	y_in = (float *)calloc(sizeof(float),pattern->numCategories);

	/*Neuron Outputs*/
	z = (float *)calloc(sizeof(float),numHiddenLayerNeurons);
	y = (float *)calloc(sizeof(float),pattern->numCategories);


	for(p=numFirstPattern; p<pattern->numPatterns ;p++)
	{

		if(1)
		{
			printf("%d:",p+1);
			for (i=0; i<pattern->numCategories; i++)
			{
				printf("%d",(pattern->categories[p][i])>0);

			}
		
			printf("| ");
		}

		/*Propagación hacia adelante*/
		for (i=0; i<numHiddenLayerNeurons; i++)
		{
			z_in[i] = bias[i];
			for (j=0; j<pattern->numAttributes; j++)
				z_in[i] += weightsV[i][j] * pattern->attributes[p][j];
			
			z[i] = (2/(1+exp(-z_in[i])))-1;

			if(1)
			{
				printf("%.2f ",z[i]);
				//printf("ZIN[%d] = %.6f\n",i,z_in[i]);
			}
				
		}
		if(1) printf("\n");

		//max = INT_MIN;
		hits = 0;
		for (i=0; i<pattern->numCategories; i++)
		{
			
			y_in[i] = bias[numHiddenLayerNeurons+i];

			for (j=0; j<numHiddenLayerNeurons; j++)
				y_in[i] += weightsW[i][j]*z[j];

			if(DEBUG_TEST)
				printf("Y_IN %.2f\n",y_in[i]);

			y[i] = (2/(1+exp(-y_in[i])))-1;
			if(DEBUG_TEST){
				printf("Y[%d] = %.10f\n",i,y[i]);
				printf("T[%d] = %.10f\n",i,pattern->categories[p][i]);
			}
			if(((y[i] > 0) && (pattern->categories[p][i] > 0))
				|| ((y[i] <= 0) && (pattern->categories[p][i] < 0)))
			{
				hits++;
			}
		}

		printf("%d) Pixeles fallados %.2f\n",p+1,
			(float)(pattern->numCategories-hits)/pattern->numCategories*100);
			

	}
	//printf("Test : ACIERTOS = %d %.0f%%\n",hits,
	//(float)hits/numPatterns*100);
	//printf("Test FALLOS = %d %.0f%%\n",numPatterns - hits,
	//(float)(numPatterns - hits)/numPatterns*100);
/*
	printf("ACIERTOS = %d %d%%\n",hits/pattern->numCategories,
		hits/pattern->numCategories/(pattern->numPatterns-numFirstPattern)*100);*/

	free(y);
	free(z);
	free(z_in);
	free(y_in);

	return 1;
}