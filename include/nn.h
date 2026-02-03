#pragma once

// typedef struct Layer Layer;

typedef struct Layer {
  Matrix *input;
  Matrix *weights;
  Matrix *biases;

  Matrix *delta;
  Matrix *grads;

  float (*activation)(float x);
  float (*gradient)(float x);
} Layer;

typedef struct NeuronFunction {
  float (*activation)(float x);
  float (*gradient)(float x);
} NeuronFunction;

typedef struct Model {
  Layer *layers[];
} Model;

float sigmoid__activation   (float x);
float sigmoid__gradient     (float x);

float softplus__activation  (float x);
float softplus__gradient    (float x);

float tanh__activation      (float x);
float tanh__gradient        (float x);


Layer* Layer__create(size_t input, size_t output, const NeuronFunction* nf);


Matrix* Model__forward(Layer *layers[], size_t len);

