#include "s21_matrix.h"

int s21_calc_complements(matrix_t *A, matrix_t *result) {
  if (s21_matrix_exist(*A)) {
    return NOT_EXIST;
  }

  if (A->rows != A->columns) {
    return INCOMPATIBLE;
  }

  int code = s21_create_matrix(A->rows, A->columns, result);
  if (code == 0) {
    code = algebraic_expressions(A, result);
  }

  return code;
}

int algebraic_expressions(matrix_t *A, matrix_t *result) {
  result->matrix[0][0] = 1;

  if (A->rows == 1) {
    return OK;
  }

  int code = OK;
  for (int i = 0; i < A->rows; i++) {
    for (int j = 0; j < A->columns; j++) {
      double deted;
      matrix_t minored;

      code = calc_minor(i + 1, j + 1, A, &minored);
      if (code != 0) {
        s21_remove_matrix(&minored);
        break;
      }

      code = s21_determinant(&minored, &deted);
      s21_remove_matrix(&minored);

      if (code != 0) {
        break;
      }

      result->matrix[i][j] = (i + j) % 2 == 0 ? deted : -deted;
    }
    if (code != 0) {
      break;
    }
  }

  return code;
}

int calc_minor(int row, int column, matrix_t *A, matrix_t *result) {
  if (A->matrix == NULL) {
    return NOT_EXIST;
  }

  int code = s21_create_matrix(A->rows - 1, A->columns - 1, result);
  if (code != 0) {
    return code;
  }

  int m = 0;
  for (int i = 0; i < A->rows; i++) {
    if (i == row - 1) {
      continue;
    }

    int n = 0;
    for (int j = 0; j < A->columns; j++) {
      if (j == column - 1) {
        continue;
      }

      result->matrix[m][n] = A->matrix[i][j];
      n++;
    }
    m++;
  }
  return OK;
}

