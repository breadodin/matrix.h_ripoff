#include "s21_matrix.h"

int s21_inverse_matrix(matrix_t *A, matrix_t *result) {
  if (s21_matrix_exist(*A)) {
    return NOT_EXIST;
  }

  double determinant;
  int code = s21_determinant(A, &determinant);
  if (code != 0) {
    return code;
  }

  if (fabs(determinant) < EPSILON) {
    return INCOMPATIBLE;
  }

  matrix_t tmp_calc;
  code = s21_calc_complements(A, &tmp_calc);
  if (code != 0) {
    return code;
  }

  matrix_t tmp_trans;
  code = s21_transpose(&tmp_calc, &tmp_trans);
  if (code != 0) {
    s21_remove_matrix(&tmp_calc);
    return code;
  }

  code = s21_mult_number(&tmp_trans, 1.0 / determinant, result);
  s21_remove_matrix(&tmp_trans);
  s21_remove_matrix(&tmp_calc);

  return code;
}

