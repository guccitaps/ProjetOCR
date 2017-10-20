#include <stdlib.h>
#include <stdio.h>

struct Edge{
int origin;
int destination;
double weight;
};

/*
remplace with double[]
0 -> origin
1 -> destination
2 -> weight

*/

void activation(double* entries, int values[], int len)
{ // len -> amount of entries
	for (int i = 0; i < len; i++)
	{
		*(entries + i) = values[i];
	}
}


void propagation(double* neurons, double edges[], int nbNeurons, int nbEdges)
{
 for (int i = 2; i < nbNeurons; i++) // 2 -> 2 entries 
 {
	double sum = 0;
	for (int j = 0; j < nbEdges; j++)
	{
//		printf("%lf\n", edges[j * 3 + 1 ]);
		if (edges[j * 3 + 1] == i)
		{
			sum += *(neurons +(int) edges[j * 3]) * edges[j * 3 + 2];
			
//			printf("neuron visited : %d : %lf added with weight %lf from %lf\n", i, *(neurons + j), *(edges + j * 3 + 2), *(edges + j * 3));
		}
	}
	*(neurons + (int)i) = sum;
//	printf("new value : %lf\n", sum);
  }

}

double errorCalculation(double value, double expected_value)
{
	// XOr -> one dimension only -> simplified error calculation
	value = value > 0 ? -1 : 1;
	return expected_value - value;
}

void correction_propagation(double neurons[], double* edges, int nbNeurons, int nbEdges, double error, double coef)
{
  for (int i = 0; i < nbEdges; i++)
  {	
	int cast = (int)*(edges + 3 * i);
	double prod = coef * error * neurons[cast];
	int k = i;
	while ( *(edges + 3 * k + 1) < nbNeurons - 1 )
	{
		prod *= *(edges + 3 * k + 2);
		k++;
	}
	*(edges + 3 * i + 2) += prod;
  }  
}





int main(int argc, char* argv[])
{

  int nbNeurons = 5;
  int nbEdges = 6;

  double correctionCoef = 0.1;
/*
     A       B
     ||     ||
     | |   | |
     |  | |  |
     |   |   |
     |  | |  |
     | |   | |
     A2     B2
      |     |
       |   |
         A3
*/
  double neurons[nbNeurons];
  /*
  neurons 
	0 : A
	1 : B
	2 : A2
	3 : B2
	4 : A3
  */

  double edges[nbEdges * 3];
  /*
  edge  0 : A -> A2
	1 : A -> B2
	2 : B -> A2
	3 : B -> B2
	4 : A2 -> A3
	5 : B2 -> A3	 
    */

	edges[0]/*.origin*/ = 0;
	edges[1]/*.destination*/ = 2;
	edges[2]/*.weight*/ = 0.2;

	edges[3] = 0;
	edges[4] = 3;
	edges[5] = 0.2;

	edges[6] = 1;
	edges[7] = 2;
	edges[8] = 0.2;

	edges[9] = 1;
	edges[10] = 3;
	edges[11] = 0.2;

	edges[12] = 2;
	edges[13] = 4;
	edges[14] = 0.2;

	edges[15] = 3;
	edges[16] = 4;
	edges[17] = 0.2;

	double* neurons_p = neurons;
	double* edges_p = edges;
	
	

	for (int z = 0; z < 100; z++)
	{
		int value0 = rand() % 2;
		int value1 = rand() % 2;
		
//		printf("value0: %d\n", value0);
//		printf("value1: %d\n", value1);
	
		double expectedValue = value0 != value1 ? 1 : -1;

		int entries[2];
		entries[0] = value0;
		entries[1] = value1;
		activation(neurons_p, entries, 2);
		propagation(neurons_p, edges, nbNeurons, nbEdges);
		double error = errorCalculation(neurons[nbNeurons - 1], 1);
		correction_propagation(neurons, edges_p, nbNeurons, nbEdges, error, correctionCoef);

		printf("%d : %lf\n", z, error);

/*		for(int i = 0; i < nbNeurons; i++)
		{
			printf("neurons state:\n");
			printf("%d : %lf\n", i, neurons[i]);
		}
	
		for(int i = 0; i < nbEdges; i++)
		{
			printf("edges state:\n");
			printf("%d : %lf\n", i, edges[3 * i + 2]);
		}
*/
	}


		for(int i = 0; i < nbNeurons; i++)
		{
			printf("neurons state:\n");
			printf("%d : %lf\n", i, neurons[i]);
		}
	
		for(int i = 0; i < nbEdges; i++)
		{
			printf("edges state:\n");
			printf("%d : %lf\n", i, edges[3 * i + 2]);
		}
  return 0;
}
