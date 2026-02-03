

// #include <stddef.h> // size_t if do not need stdlib;
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "matrix.h"


void Matrix__init(Matrix* self, size_t rows, size_t cols) {
  self->rows = rows;
  self->cols = cols;
  self->transpose = false;
}

Matrix* Matrix__create(size_t rows, size_t cols) {
  Matrix* matrix = malloc( sizeof(Matrix) + rows * sizeof(float *));

  for (size_t i = 0; i < rows; i++) {
    matrix->array[i] = malloc(cols * sizeof(float));
  }

   Matrix__init(matrix, rows, cols);
   return matrix;
}

Matrix* Matrix__createPointer(Matrix* self) {
  Matrix* matrix = malloc( sizeof(Matrix) + self->rows * sizeof(float *));
  for (size_t i = 0; i < self->rows; i++) {
    matrix->array[i] = self->array[i];
  }

  Matrix__init(matrix, self->rows, self->cols);

  return matrix;
}

void Matrix__setValue(Matrix* self, size_t row, size_t col, float value) {
  if (self->transpose) {
    self->array[col][row] = value;
  } else {
    self->array[row][col] = value; 
  }
}

float Matrix__getValue(const Matrix* self, size_t row, size_t col) {
  if (self->transpose) {
    return self->array[col][row];
  } else {
    return self->array[row][col];
  }
}

size_t Matrix__getRows(const Matrix* self) {
  if (self->transpose) {
    return self->cols;
  } else {
    return self->rows;
  }
};

size_t Matrix__getCols(const Matrix* self) {
  if (self->transpose) {
    return self->rows;
  } else {
    return self->cols;
  }
};

void Matrix__transpose(Matrix* self) { self->transpose = !self->transpose; }


// void Matrix__malloc(Matrix* self, size_t rows, size_t cols) {
//   self = malloc( sizeof(Matrix) + rows * sizeof(float *));
//   for (size_t i = 0; i < rows; i++) {
//     self->array[i] = malloc(cols * sizeof(float));
//   }
//   Matrix__init(self, rows, cols);
// }

// Destructor (without deallocation)
void Matrix__reset(Matrix* self) {
  for (size_t i = 0; i < self->rows; i++) {
    // free(self->array[i]);
    // self->array[i] = (float*)calloc(self->cols, sizeof(float));
    memset(self, 0, self->cols * sizeof(float)); 
  }
}

// Destructor + deallocation (equivalent to "delete point")
void Matrix__destroy(Matrix* self) {
  if (self) {
    // Matrix__reset(self);

    for (size_t i = 0; i < self->rows; i++) {
      free(self->array[i]);
    }
    free(self);
  }
}

void Matrix__destroyPointer(Matrix* self_ptr) {
  if (self_ptr) {
    free(self_ptr);
  }
}

void Matrix__fill(Matrix* self, float value) {
  size_t rows = Matrix__getRows(self);
  size_t cols = Matrix__getCols(self);

  for (size_t r = 0; r < rows; r++) {
    for (size_t c = 0; c < cols; c++) {
      Matrix__setValue(self, r, c, value);
    }
  }
};

void Matrix__fillRandom(Matrix* self) {
  size_t rows = Matrix__getRows(self);
  size_t cols = Matrix__getCols(self);

  for (size_t r = 0; r < rows; r++) {
    for (size_t c = 0; c < cols; c++) {
      float value = (float)(rand() % 1000) / 1000;
      Matrix__setValue(self, r, c, value);
    }
  }
};

void Matrix__multiply(Matrix* self, const Matrix* A, const Matrix* B) {
  // Matrix* matrix = Matrix__create(self_1->rows, self_2->cols);

  size_t self_rows = Matrix__getRows(self);
  size_t self_cols = Matrix__getCols(self);

  size_t A_rows = Matrix__getRows(A);
  size_t A_cols = Matrix__getCols(A);

  size_t B_rows = Matrix__getRows(B);
  size_t B_cols = Matrix__getCols(B);

  if (
    A_cols == B_rows    &&
    A_rows == self_rows &&
    B_cols == self_cols
  ) {
    for (size_t r = 0; r < A_rows; r++) {
      for (size_t c = 0; c < B_cols; c++) {
        float tmp = 0;
        for (size_t i = 0; i < B_rows; i++) {
          tmp += Matrix__getValue(A, r, i) * 
                 Matrix__getValue(B, i, c);
        }
        Matrix__setValue(self, r, c, tmp);
      }
    }
  } else {
    printf("Error! Size of cols matrix1 is not equals size of rows matrix2. \n");
    printf("self: rows %d, cols %d \n", self_rows, self_cols);
    printf("A: rows %d, cols %d \n", A_rows, A_cols);
    printf("B: rows %d, cols %d \n", B_rows, B_cols);
  }
}


void Matrix__canvasAdd(Matrix* self, const Matrix* A, const Matrix* B) {

  size_t self_rows = Matrix__getRows(self);
  size_t self_cols = Matrix__getCols(self);

  size_t A_rows = Matrix__getRows(A);
  size_t A_cols = Matrix__getCols(A);

  size_t B_rows = Matrix__getRows(B);
  size_t B_cols = Matrix__getCols(B);

 
  if (self_cols == A_cols &&
      self_rows == A_rows
  ) {
    for (size_t r = 0; r < A_rows; r++) {
      for (size_t c = 0; c < A_cols; c++) {
        // self->array[r][c] = A->array[r][c] + B->array[r % B->rows][c % B->cols];
        float tmp = Matrix__getValue(A, r, c) +
                    Matrix__getValue(B, r % B_rows, c % B_cols);
        Matrix__setValue(self, r, c, tmp);
      }
    }
  } else {
    printf("Error! Size of rows and cols matrix self is not equals size of rows and cols matrix A. \n");
  }
}

void Matrix__canvasSubtract(Matrix* self, const Matrix* A, const Matrix* B) {

  size_t self_rows = Matrix__getRows(self);
  size_t self_cols = Matrix__getCols(self);

  size_t A_rows = Matrix__getRows(A);
  size_t A_cols = Matrix__getCols(A);

  size_t B_rows = Matrix__getRows(B);
  size_t B_cols = Matrix__getCols(B);

 
  if (self_cols == A_cols &&
      self_rows == A_rows
  ) {
    for (size_t r = 0; r < A_rows; r++) {
      for (size_t c = 0; c < A_cols; c++) {
        // self->array[r][c] = A->array[r][c] + B->array[r % B->rows][c % B->cols];
        float tmp = Matrix__getValue(A, r, c) -
                    Matrix__getValue(B, r % B_rows, c % B_cols);
        Matrix__setValue(self, r, c, tmp);
      }
    }
  } else {
    printf("Error! Size of rows and cols matrix self is not equals size of rows and cols matrix A. \n");
  }
}

void Matrix__canvasMultiply(Matrix* self, const Matrix* A, const Matrix* B) {

  size_t self_rows = Matrix__getRows(self);
  size_t self_cols = Matrix__getCols(self);

  size_t A_rows = Matrix__getRows(A);
  size_t A_cols = Matrix__getCols(A);

  size_t B_rows = Matrix__getRows(B);
  size_t B_cols = Matrix__getCols(B);

 
  if (self_cols == A_cols &&
      self_rows == A_rows
  ) {
    for (size_t r = 0; r < A_rows; r++) {
      for (size_t c = 0; c < A_cols; c++) {
        // self->array[r][c] = A->array[r][c] + B->array[r % B->rows][c % B->cols];
        float tmp = Matrix__getValue(A, r, c) *
                    Matrix__getValue(B, r % B_rows, c % B_cols);
        Matrix__setValue(self, r, c, tmp);
      }
    }
  } else {
    printf("Error! Size of rows and cols matrix self is not equals size of rows and cols matrix A. \n");
  }
}

void Matrix__canvasDivide(Matrix* self, const Matrix* A, const Matrix* B) {

  size_t self_rows = Matrix__getRows(self);
  size_t self_cols = Matrix__getCols(self);

  size_t A_rows = Matrix__getRows(A);
  size_t A_cols = Matrix__getCols(A);

  size_t B_rows = Matrix__getRows(B);
  size_t B_cols = Matrix__getCols(B);

 
  if (self_cols == A_cols &&
      self_rows == A_rows
  ) {
    for (size_t r = 0; r < A_rows; r++) {
      for (size_t c = 0; c < A_cols; c++) {
        // self->array[r][c] = A->array[r][c] + B->array[r % B->rows][c % B->cols];
        float tmp = Matrix__getValue(A, r, c) *
                    Matrix__getValue(B, r % B_rows, c % B_cols);
        Matrix__setValue(self, r, c, tmp);
      }
    }
  } else {
    printf("Error! Size of rows and cols matrix self is not equals size of rows and cols matrix A. \n");
  }
}

void Matrix__unaryFunction(Matrix* self, float (*function)(float)) {
  size_t rows = Matrix__getRows(self);
  size_t cols = Matrix__getCols(self);

  for (size_t r = 0; r < rows; r++) {
    for (size_t c = 0; c < cols; c++) {
      float value = Matrix__getValue(self, r, c);
      value = function(value);
      Matrix__setValue(self, r, c, value);
    }
  }
}

void Matrix__display(const Matrix* self) {
  size_t rows = Matrix__getRows(self);
  size_t cols = Matrix__getCols(self);

  for (size_t r = 0; r < rows; r++) {
    for (size_t c = 0; c < cols; c++) {
      float value = Matrix__getValue(self, r, c);
      printf("%f ", value);
    }
    printf("\n");
  }
}

