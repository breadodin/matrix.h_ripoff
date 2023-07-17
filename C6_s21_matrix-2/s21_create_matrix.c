#include "s21_matrix.h"

int s21_create_matrix(int rows, int columns, matrix_t *result) {
  int code = OK;
  if (rows < 1 || columns < 1) {
    code = NOT_EXIST;
  } else {
    result->matrix = (double **)malloc(rows * sizeof(double *) +
                                       rows * columns * sizeof(double));
    if (result->matrix != NULL) {
      double *start =
          (double *)((char *)result->matrix + rows * sizeof(double *));
      for (int i = 0; i < rows; ++i) {
        result->matrix[i] = start + i * columns;
        for (int j = 0; j < columns; ++j) {
          result->matrix[i][j] = 0.0;
        }
      }
    } else {
      code = INCOMPATIBLE;
    }
  }
  result->rows = rows;
  result->columns = columns;
  result->initialized = false;
  return code;
}
