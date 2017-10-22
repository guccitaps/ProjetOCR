#include <stdlib.h>
#include <stdio.h>
#include <math.h>


/*
remplace with double[]
0 -> origin
1 -> destination
2 -> weight

*/

double sigmoid(double x)
{
	return (1 / (1 + exp(-x)));
}

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
		if (edges[j * 3 + 1] == i)
		{
			sum += *(neurons +(int) edges[j * 3]) * edges[j * 3 + 2];
			
		}
	}
	*(neurons + (int)i) = sigmoid(sum);
  }

}

double errorCalculation(double value, double expected_value)
{
	// XOr -> one dimension only -> simplified error calculation
	return expected_value - value;
}

double NeuronError(double neurons[], double* edges, int nbNeurons, int nbEdges, double expectedValue, int i)
{
  if (i == nbNeurons - 1)
  {
	
	double ret =  neurons[i] * (1 - neurons[i]) * (expectedValue - neurons[nbNeurons - 1]);
//	printf("------ O : %d : %lf\n", i, ret);
	return ret; 
  }
  else
  {
 	 double prod = neurons[i] * (1 - neurons[i]);
 	 double sum = 0;
  	for (int j = 0; j < nbEdges; j++)
  	{
		if (*(edges + j * 3) == i)
		{
		 	double ret = NeuronError(neurons, edges, nbNeurons, nbEdges, expectedValue, *(edges + j * 3 + 1));
			
//			printf("------ H : %d : %lf\n", i, ret);
			sum += ret;
 			sum *= *(edges + j * 3 + 2);
		}
	 }
	
  	return prod * sum;
  }

}

void back_propagation(double neurons[], double* edges, int nbNeurons, int nbEdges, double expectedValue, double coef)
{
	//update hidden -> output edges weights

	for (int i = 0; i < nbEdges; i++)
	{
		if (*(edges + 3 * i + 1) == nbNeurons-1)
		{
			double error = NeuronError(neurons, edges, nbNeurons, nbEdges, expectedValue, nbNeurons - 1);
			*(edges + 3 * i + 2) += (coef * error * neurons[(int)*(edges + 3 * i)]);
		}
	}
	// update input -> hidden edges weights
	for (int i = 0; i < nbEdges; i++)
	{
		if(*(edges + 3 * i + 1) != nbNeurons-1)
		{
			double error = NeuronError(neurons, edges, nbNeurons, nbEdges, expectedValue, *(edges + 3 * i + 1));	
			*(edges + 3 * i + 2) += (coef * error * neurons[(int)*(edges + 3 * i)]);
		}
	}
}





int main(int argc, char* argv[])
{
	
	argc++;
	argv++;
  int nbNeurons = 6;
  int nbEdges = 7;

  double correctionCoef = 0.1;
  double neurons[nbNeurons];
  
/*
	  neurons 
	0 : A
	1 : B
	2 : A2
	3 : C
	4 : C2
	5 : A3
  */

  double edges[nbEdges * 3];
  /*
  edge  0 : A  -> A2
	1 : A  -> A3
	2 : B  -> A2
	3 : B  -> A3
	4 : A2 -> A3
	5 : C  -> A2	 
	6 : C2 -> A3
    */

	edges[0]/*.origin*/ = 0;
	edges[1]/*.destination*/ = 2;
	edges[2]/*.weight*/ = 0;

	edges[3] = 0;
	edges[4] = 5;
	edges[5] = 0;

	edges[6] = 1;
	edges[7] = 2;
	edges[8] = 0;

	edges[9] = 1;
	edges[10] = 5;
	edges[11] = 0;

	edges[12] = 2;
	edges[13] = 5;
	edges[14] = 0;

	edges[15] = 3;
	edges[16] = 2;
	edges[17] = 0;

	edges[18] = 4;
	edges[19] = 5;
	edges[20] = 0;
	
	// bias initialisation
	neurons[3] = 1;
	neurons[4] = 1;

	double* neurons_p = neurons;
	double* edges_p = edges;
	
	//tests
	neurons[2] = 0.5;
	neurons[5] = 0.5;

	

	for (int z = 0; z < 100000; z++)
	{
		int value0 = rand() % 2;
		int value1 = rand() % 2;
	
		double expectedValue = value0 != value1 ? 1 : 0;

		int entries[2];
		entries[0] = value0;
		entries[1] = value1;
		activation(neurons_p, entries, 2);
		propagation(neurons_p, edges, nbNeurons, nbEdges);
		back_propagation(neurons, edges_p, nbNeurons, nbEdges, expectedValue, correctionCoef);

		printf("%d : %d : %d :  %lf\n", z, value0, value1, neurons[nbNeurons - 1]);


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
