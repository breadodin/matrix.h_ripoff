#include "s21_matrix.h"

int s21_eq_matrix(matrix_t *matrix_one, matrix_t *matrix_two) {
  if (s21_matrix_exist(*matrix_one) || s21_matrix_exist(*matrix_two)) {
    return SUCCESS;
  }

  if (matrix_one->columns != matrix_two->columns ||
      matrix_one->rows != matrix_two->rows) {
    return FAILURE;
  }

  int equality = SUCCESS;
  for (int i = 0; i < matrix_one->rows; i++) {
    for (int j = 0; j < matrix_one->columns; j++) {
      double diff = fabs(matrix_one->matrix[i][j] - matrix_two->matrix[i][j]);
      if (diff >= EPSILON) {
        equality = FAILURE;
      }
    }
  }

  return equality;
}

