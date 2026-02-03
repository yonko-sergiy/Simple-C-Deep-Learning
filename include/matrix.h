
#pragma once


// typedef struct Matrix Matrix;
typedef struct Matrix {
  size_t cols;
  size_t rows;
  bool   transpose;
  float *array[];
} Matrix;

// struct Matrix;
// Constructor (without allocation)
void Matrix__init(Matrix* self, size_t rows, size_t cols);

// Allocation + initialization (equivalent to "new Point(x, y)")
Matrix* Matrix__create(size_t rows, size_t cols);
Matrix* Matrix__createPointer(Matrix* self);

void Matrix__setValue(Matrix* self, size_t row, size_t col, float value);
float Matrix__getValue(const Matrix* self, size_t row, size_t col);

size_t Matrix__getRows(const Matrix* self);
size_t Matrix__getCols(const Matrix* self);


void Matrix__transpose(Matrix* self);

// void Matrix__malloc(Matrix* self, size_t rows, size_t cols) {
//   self = malloc( sizeof(Matrix) + rows * sizeof(float *));
//   for (size_t i = 0; i < rows; i++) {
//     self->array[i] = malloc(cols * sizeof(float));
//   }
//   Matrix__init(self, rows, cols);
// }

// Destructor (without deallocation)
void Matrix__reset(Matrix* self);

// Destructor + deallocation (equivalent to "delete point")
void Matrix__destroy(Matrix* self);
void Matrix__destroyPointer(Matrix* self);

void Matrix__fill(Matrix* self, float value);
void Matrix__fillRandom(Matrix* self);

void Matrix__multiply(Matrix* self, const Matrix* A, const Matrix* B);


void Matrix__canvasAdd      (Matrix* self, const Matrix* A, const Matrix* B);
void Matrix__canvasSubtract (Matrix* self, const Matrix* A, const Matrix* B);
void Matrix__canvasMultiply (Matrix* self, const Matrix* A, const Matrix* B);
void Matrix__canvasDivide   (Matrix* self, const Matrix* A, const Matrix* B);

void Matrix__unaryFunction  (Matrix* self, float (*function)(float));

void Matrix__display(const Matrix* self);

