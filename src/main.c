
#include <stdlib.h>
#include <stdio.h>

#include "matrix.h"
#include "nn.h"


int main(int argc, char *argv[])
{

  NeuronFunction sigmoid = {sigmoid__activation, sigmoid__gradient};

  Layer *myLayers[2] = {
    Layer__create(3, 4, &sigmoid),
    Layer__create(4, 2, &sigmoid)
  };

  // myLayers[0] = Layer__create(3, 4, &sigmoid);
  // myLayers[1] = Layer__create(3, 4, &sigmoid);

  // Matrix__multiply(myLayers[1]->input, myLayers[0]->input, myLayers[0]->weights);
  // Matrix__canvasAdd(myLayers[1]->input, myLayers[1]->input, myLayers[0]->biases);
  // Matrix__unaryFunction(myLayers[1]->input, myLayers[0]->activation);
  //
  Matrix *result = Model__forward(myLayers, 2);

  Matrix__display(result);


  // Matrix__fillRandom(myLayers[0]->input);
  // Matrix__fillRandom(myLayers[0]->input);
  // Matrix__display(myLayers[0]->input);
  // printf("%f\n", myLayers[0]->activation(3));
  // printf("%f\n", myLayers[0]->gradient(3));
  //
  // Matrix *matrixA = Matrix__create(4, 1);
  // Matrix *matrixB = Matrix__create(4, 1);

  //
  // Matrix__transpose(matrixB);
  // Matrix__fill(matrixA, .3);
  // Matrix__fill(matrixB, .3);

  // Matrix__fillRandom(matrixB);
  // Matrix__fillRandom(matrixB);

  // Matrix__fillRandom(matrixB);
  // Matrix__display(matrixB);

  // Matrix__unaryFunction(matrixB, sigmoid__gradient);
  // Matrix__display(matrixB);


  // matrixB->array[0][0] = 0;
  // matrixB->array[0][2] -= 3;

  // Matrix *matrixC = Matrix__create(4, 4);
  //
  // Matrix__multiply(matrixC, matrixA, matrixB);

  // Matrix__display(matrixA);
  // Matrix__display(matrixB);
  // Matrix__display(matrixC);


  // Matrix__destroy(matrixA);
  // Matrix__destroy(matrixC);
  // Matrix__destroy(matrixB);
  //
  //
  // Matrix *A = Matrix__create(4, 4);
  // Matrix *B = Matrix__create(2, 2);
  // Matrix__fill(A, .3);
  // Matrix__fillRandom(B);
  //
  // Matrix__canvasAdd(A, A, B);
  // printf("\n");
  // Matrix__display(A);


  return EXIT_SUCCESS;
}
