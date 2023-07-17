#include "s21_matrix.h"

int s21_sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  if (s21_matrix_exist(*A) || s21_matrix_exist(*B)) {
    return NOT_EXIST;
  }

  if (A->rows != B->rows || A->columns != B->columns) {
    return INCOMPATIBLE;
  }

  int code = s21_create_matrix(A->rows, A->columns, result);
  if (code != 0) {
    return code;
  }

  for (int i = 0; i < A->rows; i++) {
    for (int j = 0; j < A->columns; j++) {
      result->matrix[i][j] = A->matrix[i][j] - B->matrix[i][j];
    }
  }

  return OK;
}

