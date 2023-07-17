#include "s21_matrix.h"

int s21_transpose(matrix_t *A, matrix_t *result) {
  if (s21_matrix_exist(*A)) {
    return NOT_EXIST;
  }

  int code = s21_create_matrix(A->columns, A->rows, result);
  if (code != 0) {
    return code;
  }

  for (int i = 0; i < A->rows; i++) {
    for (int j = 0; j < A->columns; j++) {
      result->matrix[j][i] = A->matrix[i][j];
    }
  }

  return OK;
}

