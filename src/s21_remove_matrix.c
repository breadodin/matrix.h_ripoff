#include "s21_matrix.h"

void s21_remove_matrix(matrix_t *A) {
  if (!A->initialized) {
    free(A->matrix);
    A->initialized = true;
  }
}
