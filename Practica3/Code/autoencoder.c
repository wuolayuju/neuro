

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