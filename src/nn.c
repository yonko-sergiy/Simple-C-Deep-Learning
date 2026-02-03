
#include <stdlib.h>
#include <math.h>

#include "matrix.h"
#include "nn.h"


float sigmoid__activation (float x) { return 1 / (1 + exp(-x)); }
float sigmoid__gradient   (float x) { return sigmoid__activation(x) * (1 - sigmoid__activation(x)); }

float softplus_activation (float x) { return log(1 + exp(x)); }
float softplus_gradient   (float x) { return sigmoid__activation(x); }

float tanh__activation    (float x) { return tanh(x); }
float tanh__gradient      (float x) { return 1 - tanh(x); }


Layer* Layer__create(size_t input, size_t output, const NeuronFunction* nf) {
  Layer* layer = malloc(sizeof(Layer));

  layer->input   = Matrix__create(1, input);
  layer->weights = Matrix__create(input, output);
  layer->biases  = Matrix__create(output, 1);

  layer->delta   = Matrix__create(1, output);
  layer->grads   = Matrix__create(input, output);

  layer->activation = nf->activation;
  layer->gradient   = nf->gradient;

  Matrix__fill(layer->input, 0);
  Matrix__fillRandom(layer->weights);
  Matrix__fillRandom(layer->biases);

  Matrix__fill(layer->delta, 0);
  Matrix__fill(layer->grads, 0);

  return layer;
}


Matrix* Model__forward(Layer *layers[], size_t len) {
  for (size_t i = 0; i < len - 1; i++) {
    Matrix__multiply(layers[i + 1]->input,
                     layers[i]->input,
                     layers[i]->weights);

    Matrix__canvasAdd(layers[i + 1]->input,
                      layers[i + 1]->input,
                      layers[i]->biases);

    Matrix__unaryFunction(layers[i + 1]->input,
                          layers[i]->activation);
  }
  size_t rows = Matrix__getRows(layers[len - 1]->input);
  size_t cols = Matrix__getCols(layers[len - 1]->weights);

  Matrix* output = Matrix__create(rows, cols);

  Matrix__multiply(output,
                   layers[len - 1]->input,
                   layers[len - 1]->weights);

  Matrix__canvasAdd(output,
                    output,
                    layers[len - 1]->biases);

  Matrix__unaryFunction(output,
                        layers[len - 1]->activation);

  return output;
}
