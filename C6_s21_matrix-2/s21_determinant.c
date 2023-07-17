#include "s21_matrix.h"

int s21_determinant(matrix_t *A, double *result) {
  if (s21_matrix_exist(*A)) {
    return NOT_EXIST;
  }

  if (A->columns != A->rows) {
    return INCOMPATIBLE;
  }

  double p = 1.0;
  matrix_t T;
  matrix_t O;
  s21_create_matrix(A->rows, A->columns, &T);
  s21_create_matrix(A->rows, A->columns, &O);

  memcpy(O.matrix[0], A->matrix[0], A->rows * A->columns * sizeof(double));

  for (int r = 0; r < A->rows; r++) {
    sub_determinant(A, &T, &O, r, p);
    p = O.matrix[r][r];

    memcpy(O.matrix[0], T.matrix[0], A->rows * A->columns * sizeof(double));
  }

  *result = p;
  s21_remove_matrix(&T);
  s21_remove_matrix(&O);

  return OK;
}

void sub_determinant(matrix_t *A, matrix_t *T, matrix_t *O, int r, double p) {
  for (int i = 0; i < A->rows; i++) {
    if (i != r) {
      for (int j = 0; j < A->columns; j++) {
        T->matrix[i][j] = (O->matrix[r][r] * O->matrix[i][j] -
                           O->matrix[i][r] * O->matrix[r][j]) /
                          p;
      }
    }
  }
}

