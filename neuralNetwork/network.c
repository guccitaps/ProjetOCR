#include <stdio.h>
#include <stdlib.h>
#include <math.h> // pour l'exponentielle
#include <time.h> // Pour l'initialisation random des poids

#include "network.h"

int examples[12] = [0,0,0,0,1,1,1,0,1,1,1,0]

int activation(int (*entries)[], int (*weights)[], int size, int biais[])
 {	
	int sum = 0;
	for(unsigned i = 0; i < size; i++)
	{
		sum += &(entries+i) * &(weight+i);
	}

	sum += biais[0] * biais[1];

	return sigmoide(sum);	
 }

int sigmoide(int x)
{
	return( 1/(1+exp(-x)))
}

int main(int argc, char* argv[])
{
	int neurons[2]; // 1 -> activated ; 0 -> not
	int weights[6] = {0,0,0,0,0,0}; // On initialise les poids à 0 
	int biais1[2] = {1,0};
	int biais2[2] = {1,0};
	
	for ( int i = 0; i < argv[1]; i++ )
	{
		neurone[0] = activation(*examples[(3*i)%12], *weights[(2*i)], 2, biais1);  
		neurone[1] = activation(
	//analyse

	//find answer

	//correction
	return 0;
}

int[] create_entry(int examples[], int examples_index[], int neurones[], int neurones_index, int biais[])
{
	


}
