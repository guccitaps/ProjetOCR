
# ifndef NEURAL_H_
# define NEURAL_H_


void activation(double* neurons, double edges[], int nbNeurons, int nbEdges);
void propagation(double* neurons, double edges[], int nbNeurons, int nbEdges);
double errorCalculation(double value, double expected_value);
void correction_propagation(double neurons[], double* edges, int nbNeurons, int nbEdges, double error, double coef);


#endif

