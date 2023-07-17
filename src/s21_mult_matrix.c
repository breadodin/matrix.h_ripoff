#include "s21_matrix.h"

int s21_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  if (s21_matrix_exist(*A) || s21_matrix_exist(*B)) {
    return NOT_EXIST;
  }

  if (A->columns != B->rows) {
    return INCOMPATIBLE;
  }

  int code = s21_create_matrix(A->rows, B->columns, result);
  if (code != 0) {
    return code;
  }

  for (int i = 0; i < A->rows; i++) {
    for (int j = 0; j < B->columns; j++) {
      double sum = 0;
      for (int k = 0; k < A->columns; k++) {
        sum += A->matrix[i][k] * B->matrix[k][j];
      }
      result->matrix[i][j] = sum;
    }
  }

  return OK;
}

