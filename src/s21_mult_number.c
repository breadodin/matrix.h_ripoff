#include "s21_matrix.h"

int s21_mult_number(matrix_t *A, double number, matrix_t *result) {
  int code = NOT_EXIST;

  if (!s21_matrix_exist(*A)) {
    s21_create_matrix(A->rows, A->columns, result);
    if (number == 0) {
      memset(result->matrix[0], 0, A->rows * A->columns * sizeof(double));
    } else {
      sub_mult_number(A, number, result);
    }
    code = OK;
  }
  return code;
}

void sub_mult_number(matrix_t *A, double number, matrix_t *result) {
  for (int i = 0; i < A->rows; i++) {
    for (int j = 0; j < A->columns; j++) {
      result->matrix[i][j] = A->matrix[i][j] * number;
    }
  }
}
