#ifndef NETWORK_H_
#define NETWORK_H_

#include <stdlib.h>
#include <stdint.h>
#include <math.h>

struct layer {
	double*  values;
	double*  errors;
	size_t size;
	
	double* out;
	size_t nb_out;

	double* bias;

	struct layer* previous;
	struct layer* next;
};
void print_mat16(char* mat);


void propagation(struct layer* src);
double error_calculation(struct layer* layer, size_t i, double* expectedValues);
void backpropagation(struct layer* src, double coef, double* expectedValues);
double* create_edges(struct layer* layer); //links all nodes from 2 different layers to each other


struct layer* create_layer(size_t size, struct layer* next);



void activation(struct layer* layer, char* values);

char* neural_network_training(char** data, char* str, size_t len);
#endif // NETWORK_H_


