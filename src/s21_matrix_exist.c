#include "s21_matrix.h"

int s21_matrix_exist(matrix_t matrix) {
  int matrix_does = EXIST;
  if (matrix.initialized) {
    matrix_does = NOT_EXIST;
  }
  return matrix_does;
}
