#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <string.h>
#include <stdio.h>
#include "network.h"

double sigmoid(double x)
{
	return (1 / (1 + exp(-x)));
}

void print_mat16(char* mat)
{
	printf("------------------\n");
	for(size_t i = 0; i < 16; i++)
	{
		for(size_t j = 0; j < 16; j++)
		{
			printf("%d ", *(mat + 16 * i + j));
		}
		printf("\n");
	}
	printf("------------------\n");
} 
void print_layer(struct layer* layer)
{
/*
	printf("########values###########\n");
	for (size_t i = 0; i < layer->size; i++)
	{
		printf("%zu : %lf\n", i, *(layer->values + i));
	}
*/
	printf("########errors##########\n");
	for(size_t i = 0; i < layer->size; i++)
	{
		printf("%zu : %lf\n",i, *(layer->errors + i));
	}
/*	if (layer->next)
	{
		printf("#########bias###########\n");
		for(size_t i = 0; i < layer->next->size; i++)
		{
			printf("%zu : %lf\n", i, *(layer->bias + i));
		}
	}*/
	printf("#########################\n\n");
}

void propagation(struct layer* src)
{
	struct layer* dst = src->next;

	int origin = 0;
	int destination = 0;
	double weight = 0;
	size_t src_out = src->nb_out; // ?? fixed issue
	if (dst)
	{
		for(size_t i = 0; i < dst->size; i++)
		{
			*(dst->values + i) = 0;
		}
	
		for(size_t k = 0; k < src_out ; k++)
		{
			origin = (int)*(src->out + 3 * k);
			destination = (int)*(src->out + 3 * k + 1);
			weight = *(src->out + 3 * k + 2);	
			double sum = *(src->values + origin) * weight + *(src->bias + destination);
		//	printf("propagated %lf from %d to %d\n", sum, origin, destination);
			*(dst->values + destination) += *(src->values + origin) * weight + *(src->bias + destination);
		
		}

		for(size_t i = 0; i < dst->size; i++)
		{
			*(dst->values + i) = sigmoid(*(dst->values + i));
		}
		propagation(dst);
	
	}
}



void error(struct layer* layer,  double* expectedValues)
{
	double* val = layer->values;
	for(size_t i = 0; i < layer->size; i++)
	{

		if (layer->nb_out == 0)
		{
			double expectedValue = *(expectedValues + i);
			*(layer->errors + i)  = *(val + i) * (1 - *(val + i)) * (expectedValue - *(val + i));
		}
		else
		{
	
			double sum = 0;
			double prod = *(val + i) * (1 - *(val + i));
			for(size_t j = 0; j < layer->nb_out; j++)
			{
				double ret = *(layer->next->errors + (int)*(layer->out + 3 * j + 1));
				sum += ret * *(layer->out + 3 * j + 2);
			}
			*(layer->errors + i) = sum * prod;
		}
	}
 }

void backpropagation(struct layer* src, double coef, double* expected_values)
{
	error(src, expected_values);
	struct layer* dst = src->previous;
	size_t dst_index = 0;
	size_t src_index = 0;
	double error = 0;
	double node = 0;
	if (dst)
	{
		for(size_t i = 0; i < dst->nb_out; i++)
		{			//dest	
			dst_index = *(dst->out + 3 * i);
			src_index = *(dst->out + 3 * i + 1);		
			error = *(src->errors + src_index);
			node = *(dst->values + dst_index);
	//		printf("backproped : %lf : %lf\n", error, node);
			*(dst->out + 3 * i + 2) += coef * error * node; 
		}
		for(size_t i = 0; i < src->size; i++)
		{
			*(dst->bias + i) += coef * *(src->errors + i) * *(src->values + i);
		}
		backpropagation(dst, coef, expected_values);
	}

}

/*

struct layer {
	double*  values;
	size_t size;
	
	double* errors;
	double bias;

	double* out;
	size_t nb_out;

	struct layer* previous;
	struct layer* next;
};
*/




double* create_edges(struct layer* layer) {	
	struct layer* next = layer->next;
	double* edges = calloc(3 * next->size * layer->size, sizeof(double));
	int pos = 1;
	for(size_t i = 0; i < layer->size; i++)
	{
		for(size_t j = 0; j < next->size; j++)
		{
			pos = -pos;
			*(edges + 3 * next->size * i + 3 * j) = i; //src
			*(edges + 3 * next->size * i + 3 * j + 1) = j;  //dst
			*(edges + 3 * next->size * i + 3 * j + 2) = pos * 0.00001 * ((rand() % 4) + 1);  //weight

		}
	}
	return edges;
}


struct layer* create_layer(size_t size, struct layer* next)
{
	struct layer* layer = malloc(sizeof(struct layer));
	if (layer)
	{
		layer->size = size;
		layer->next = next;	
		double*	values = calloc(size, sizeof(double));
		double* errors = calloc(size, sizeof(double));	
		layer->errors = errors;
		layer->values = values;
		if (next)
		{
			layer->next->previous = layer;
			layer->nb_out = size * layer->next->size;
			layer->out = create_edges(layer);
			double* bias = calloc(next->size, sizeof(double));
			int pos = 1;
			for(size_t i = 0; i < next->size; i++)
			{
				*(bias + i) = 0.02 * (rand() % 4 + 1);
				pos = -pos;
			}	
			layer->bias = bias;
		}
		else
		{
			layer->nb_out = 0;
			layer->out = NULL;
			layer->bias = NULL;
		}
	}
	else
	{
		printf("allocation failed\n");
	}
	return layer;
} 

void print_layer_values(struct layer* layer)
{
	for (size_t i = 0; i < layer->size; i++)
	{
		printf("%zu : %lf\n", i, *(layer->values + i));
	}
}

void activation(struct layer* layer, char* values)
{
	for (size_t i = 0; i < layer->size; i++)
	{
//		printf("activation: %zu\n", i);	
		*(layer->values + i)  = (double)*(values + i);
//		printf("%zu : %lf\n", i, *(layer->values + i)); ----- OK
	}
}

void save_weights(struct layer* layer)
{
	FILE *save = fopen("save.csv", "w");
	double src;
	double dst;
	double weight;
	while (layer->next != NULL)
	{	

		for (size_t i = 0; i < layer->nb_out; i++)
		{
			src = *(layer->out + 3 * i);
			dst = *(layer->out + 3 * i + 1);
			weight = *(layer->out + 3 * i + 2);

			fprintf(save,"%lf,%lf,%lf\n", src, dst, weight); 		
		}	
		for(size_t i = 0; i < layer->next->size; i++)
		{
			fprintf(save,"%lf\n", *(layer->bias + i));
		}
		layer = layer->next;
	}
	fclose(save);
}

void recover_weights(struct layer* layer)
{
	size_t buffer_size = 1024;
	printf("recovering weights\n");
	FILE* open = fopen("save.csv", "r");
	if (open)	
	{
		char buffer[buffer_size];
	
		int pass = 0;
	
		if (open == NULL)
		{
			printf("Error while loading the file.\n");
		}
		while (layer != NULL)
		{
//		printf("entered while\n");
			for(size_t i = 0; i < layer->nb_out; i++)
			{
				pass = fscanf(open, "%s",buffer);
//				printf("recovering : %s\n", buffer);
sscanf(buffer, "%lf,%lf,%lf", (layer->out + 3 * i), (layer->out+3 * i + 1), (layer->out + 3 * i + 2));
			}		
			if (layer->next)
			{
				for(size_t i = 0; i < layer->next->size; i++)
				{
					pass = fscanf(open, "%s", buffer);
					sscanf(buffer, "%lf", (layer->bias + i));
				}
			}	
			layer = layer->next;
		}
	}
}	



void print_string(char* str)
{
	while(*str != '\0')
	{
		printf("%c", *str);
		str = str + 1;
	}
}

char* neural_network_analysis(char** data, size_t len)
{

	char* return_buffer = calloc(len, sizeof(char));

	size_t input_size = 16 * 16;
	size_t output_size = 54;
	size_t hidden_size = 128;

	struct layer* output_layer = create_layer(output_size, NULL);
	struct layer* hidden_layer3 = create_layer(hidden_size, output_layer);
	struct layer* hidden_layer2 = create_layer(hidden_size, hidden_layer3);
	struct layer* hidden_layer1 = create_layer(hidden_size,  hidden_layer2);
	struct layer* input_layer = create_layer(input_size,  hidden_layer1);	

	recover_weights(input_layer);

	char* input = calloc(input_size, sizeof(char));
	double* expected_values = calloc(output_size, sizeof(double));

	char* letter_matrix;

	
	for(size_t count = 0; count < len; count++)
	{	
		letter_matrix = *(data + count);
		for(size_t i = 0; i < 16; i++)
		{
			for(size_t j = 0; j < 16; j++)
			{
				*(input + 16 * i + j) = *(letter_matrix + 16 * i + j);		
			}
		}

		activation(input_layer, input);
		propagation(input_layer);

		size_t max = 0;
		for(size_t i = 0; i < output_layer->size; i++)
		{
			if (*(output_layer->values + i) > *(output_layer->values + max))
				max = i;
		}

		for (size_t i = 0; i < output_layer->size; i++)
		{
			*(output_layer->values + i) = 0;
		}
		for (size_t i = 0; i < hidden_layer1->size; i++)
		{
			*(hidden_layer2->values + i) = 0;
			*(hidden_layer1->values + i) = 0;
		}//same size -> opti

		if (0 <= max && max < 26) //maj
		{
			max += 65;
		}
		else if (26 <= max && max < 52)
		{
			max += 97;
		}
		else if (max == 52)
		{
			max = 44;
		}
		else
		{
			max = 46;
		}

		*(return_buffer + count) = max;
			
	}	
	return return_buffer;
	
}

double neural_network_training(char** data, char* str, size_t len)
 {
	char* pass = 0;

	size_t count = 0;	
	
	size_t MAXBUFFLEN = 1000000;
	FILE* file = fopen(str, "r");
	char* text_from_file = calloc(len, sizeof(double));

	int x = fread(text_from_file, sizeof(char), MAXBUFFLEN, file);
	if (!x)
	{
		printf("error reading file\n");
	}	
	fclose(file);
	print_string(text_from_file);

	srand(time(NULL));
	
	size_t input_size = 16 * 16;
	size_t output_size = 54;
	size_t hidden_size = 16;

	struct layer* output_layer = create_layer(output_size, NULL);
	struct layer* hidden_layer3 = create_layer(hidden_size, output_layer);
	struct layer* hidden_layer2 = create_layer(hidden_size, hidden_layer3);
	struct layer* hidden_layer1 = create_layer(hidden_size,  hidden_layer2);
	struct layer* input_layer = create_layer(input_size,  hidden_layer1);	

	char* input = calloc(input_size, sizeof(char));
	double* expected_values = calloc(output_size, sizeof(double));

	int letter_index = -1;

	double learning_rate = 0.01;

	char* letter_matrix;

	size_t correct_count = 0;
	recover_weights(input_layer);
//	len = 1;
	while(count < len)
	{	
//		print_mat16(*(data + count));
		while(letter_index < 0 && *text_from_file != '\0')
		{
			char c = *text_from_file;		
			if (*text_from_file > 64 && *text_from_file < 91)
			{
				letter_index = *text_from_file % 65;
			}
			else if (*text_from_file > 96 && *text_from_file < 123)
			{
				letter_index = *text_from_file % 97 + 26;
			}
			else if (*text_from_file == 44)
			{
				letter_index = 52;
			}
			else if (*text_from_file == 46)
			{
				letter_index = 53;
			}
			else
			{
				text_from_file = text_from_file + 1;
			}
		}

		if (letter_index == -1)
		{
			count = len;
			//stop
		}
		else
		{
		printf("expected text value : %d\n", letter_index);
		*(expected_values + letter_index) = 1;


		letter_matrix = *(data + count);
		for(size_t i = 0; i < 16; i++)
		{
			for(size_t j = 0; j < 16; j++)
			{
				*(input + 16 * i + j) = *(letter_matrix + 16 * i + j);		
			}
		}

		activation(input_layer, input);
		propagation(input_layer);
		backpropagation(output_layer, learning_rate, expected_values);


/*
		printf("%zu : hidden_layer1:\n", count);
		int x = scanf("%c", pass);
		print_layer(hidden_layer1);
		x = scanf("%c", pass);
		printf("%zu : hidden_layer2:\n", count);
		x = scanf("%c", pass);
		print_layer(hidden_layer2);
		x = scanf("%c", pass);
		printf("%zu : output_layer:\n", count);
		x = scanf("%c", pass);
*/
/*
		printf("hidden3:\n");
		print_layer(hidden_layer3);
		printf("output:\n");
		print_layer(output_layer);
		x = scanf("%c", pass);
*/
		size_t max = 0;
		for(size_t i = 0; i < output_layer->size; i++)
		{
			if (*(output_layer->values + i) > *(output_layer->values + max))
				max = i;
		}

		for (size_t i = 0; i < output_layer->size; i++)
		{
			*(output_layer->values + i) = 0;
		}
		for (size_t i = 0; i < hidden_layer1->size; i++)
		{
			*(hidden_layer3->values + i) = 0;
			*(hidden_layer2->values + i) = 0;
			*(hidden_layer1->values + i) = 0;
		}//same size -> opti
		
		printf("returned : %zu\n", max);
		printf("--------------------------\n");
		if (letter_index == max)
		{
			correct_count++;
		}


		*(expected_values + letter_index) = 0;
		letter_index = -1;
		text_from_file = text_from_file + 1;
		count++;	
	}	
	}

	printf("results : %zu / %zu\n", correct_count, count);
	save_weights(input_layer);
/*
	printf("input:\n");
	print_layer_values(input_layer);
	printf("hidden_1:\n");
	print_layer_values(hidden_layer1);
*/
//	print_layer(input_layer);
//	print_layer(hidden_layer1);
//	print_layer(output_layer);
	return correct_count / count;

}

/*
int main(int argc, char* argv)
&{
	return 0;
}
*/
