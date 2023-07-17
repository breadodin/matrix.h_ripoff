#include <check.h>
#include <setjmp.h>
#include <stdarg.h>
#include <stddef.h>
#include <stdio.h>

#include "s21_matrix.h"

#define ERROR 2
#define GREEN "\033[0;32m"
#define RESET "\033[0m"

START_TEST(test_s21_create_matrix) {
  matrix_t A;
  int ret = s21_create_matrix(4, 4, &A);
  ck_assert_int_eq(ret, 0);
  s21_remove_matrix(&A);

  ret = s21_create_matrix(-4, 4, &A);
  ck_assert_int_eq(ret, 1);

  ret = s21_create_matrix(-4, 0, &A);
  ck_assert_int_eq(ret, 1);
}
END_TEST

START_TEST(test_s21_eq_matrix) {
  matrix_t A, B;
  int ret = s21_eq_matrix(&A, &B);
  ck_assert_int_eq(ret, 1);  // Проверяем, что пустые матрицы равны
  s21_create_matrix(2, 3, &A);
  s21_create_matrix(2, 3, &B);
  A.matrix[0][0] = -49.65267543514368;
  A.matrix[0][1] = 12.377891991365175;
  A.matrix[0][2] = 13.761018865790149;
  A.matrix[1][0] = 11.904294043709768;
  A.matrix[1][1] = -13.074927184782496;
  A.matrix[1][2] = 95.49511753242501;

  B.matrix[0][0] = 80.87909370856278;
  B.matrix[0][1] = -97.35417316017332;
  B.matrix[0][2] = -33.55634101500645;
  B.matrix[1][0] = 12.260869655144873;
  B.matrix[1][1] = 61.346811351532466;
  B.matrix[1][2] = -69.43340950234091;

  ret = s21_eq_matrix(&A, &B);
  ck_assert_int_eq(ret, 0);  // Проверяем, что несовпадающие матрицы не равны
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);

  s21_create_matrix(4, 4, &A);
  s21_create_matrix(10, 10, &B);
  ret = s21_eq_matrix(&A, &B);
  ck_assert_int_eq(ret, 0);  // Проверяем, что матрицы разного размера не равны
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);

  s21_create_matrix(4, 4, &A);
  s21_create_matrix(4, 4, &B);
  A.matrix[2][3] = -7;
  ret = s21_eq_matrix(&A, &B);
  ck_assert_int_eq(
      ret, 0);  // Проверяем, что матрицы с различными элементами не равны
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);

  s21_create_matrix(4, 4, &A);
  s21_create_matrix(4, 4, &B);
  A.matrix[2][3] = -7;
  B.matrix[2][3] = -7;
  int qqq = s21_eq_matrix(&A, &B);
  ck_assert_int_eq(qqq, 1);  // Проверяем, что одинаковые матрицы равны
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(test_s21_sum_matrix) {
  matrix_t A, B, R, otvet;
  s21_create_matrix(1, 3, &A);
  s21_create_matrix(1, 3, &B);
  s21_create_matrix(1, 3, &otvet);
  // 1 число
  A.matrix[0][0] = -6.199515363767318;
  A.matrix[0][1] = 13.880273870115658;
  A.matrix[0][2] = 62.07674370678029;
  // 2 число
  B.matrix[0][0] = 13.131608011565334;
  B.matrix[0][1] = 34.06329498895013;
  B.matrix[0][2] = 46.99859232043045;
  otvet.matrix[0][0] = 6.932092647798015;
  otvet.matrix[0][1] = 47.94356885906579;
  otvet.matrix[0][2] = 109.07533602721074;
  int res = s21_sum_matrix(&A, &B, &R);
  ck_assert_int_eq(res, 0);
  int ret = s21_eq_matrix(&R, &otvet);
  ck_assert_int_eq(ret, 1);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&R);
  s21_remove_matrix(&otvet);
}
END_TEST

START_TEST(test_s21_sub_matrix) {
  matrix_t A, B, R, Z;
  s21_create_matrix(4, 2, &A);
  s21_create_matrix(4, 2, &B);
  s21_create_matrix(4, 2, &R);

  A.matrix[0][0] = 99.19670509677482;
  A.matrix[0][1] = -79.90604305070529;
  A.matrix[1][0] = -16.994623321615933;
  A.matrix[1][1] = 51.146995076338754;
  A.matrix[2][0] = -77.90811422069424;
  A.matrix[2][1] = -12.726306689436228;
  A.matrix[3][0] = 48.818893889243725;
  A.matrix[3][1] = 20.048940889955915;

  B.matrix[0][0] = 42.506384992692915;
  B.matrix[0][1] = 22.833164185563305;
  B.matrix[1][0] = 15.437986039091754;
  B.matrix[1][1] = 91.93913230409538;
  B.matrix[2][0] = 10.828981242531555;
  B.matrix[2][1] = 98.65640159583091;
  B.matrix[3][0] = 42.7627464666611;
  B.matrix[3][1] = -9.089030807221548;

  R.matrix[0][0] = 56.690320104081906;
  R.matrix[0][1] = -102.7392072362686;
  R.matrix[1][0] = -32.43260936070769;
  R.matrix[1][1] = -40.792137227756626;
  R.matrix[2][0] = -88.7370954632258;
  R.matrix[2][1] = -111.38270828526714;
  R.matrix[3][0] = 6.056147422582626;
  R.matrix[3][1] = 29.137971697177463;

  int res = s21_sub_matrix(&A, &B, &Z);
  ck_assert_int_eq(res, 0);
  int qqq = s21_eq_matrix(&R, &Z);
  ck_assert_int_eq(qqq, 1);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&R);
  s21_remove_matrix(&Z);
}
END_TEST

START_TEST(test_s21_mult_number) {
  matrix_t A, R, Z;
  s21_create_matrix(3, 3, &A);
  s21_create_matrix(3, 3, &R);

  A.matrix[0][0] = -79.03615912241548;
  A.matrix[0][1] = 24.9019063620334;
  A.matrix[0][2] = 52.19658842898403;
  A.matrix[1][0] = 68.22148804187285;
  A.matrix[1][1] = -70.397107185205;
  A.matrix[1][2] = 14.41506968562318;
  A.matrix[2][0] = -43.75507067679805;
  A.matrix[2][1] = -88.5742532669993;
  A.matrix[2][2] = 33.73455700326062;

  R.matrix[0][0] = -5981.106701822659;
  R.matrix[0][1] = 1884.4660555864116;
  R.matrix[0][2] = 3950.006785898255;
  R.matrix[1][0] = 5162.70026107374;
  R.matrix[1][1] = -5327.341488371273;
  R.matrix[1][2] = 1090.8686715201106;
  R.matrix[2][0] = -3311.190085266922;
  R.matrix[2][1] = -6702.907450293067;
  R.matrix[2][2] = 2552.8819620739455;

  int res = s21_mult_number(&A, 75.67557391748753, &Z);
  ck_assert_int_eq(res, 0);
  int qqq = s21_eq_matrix(&R, &Z);
  ck_assert_int_eq(qqq, 1);
  s21_remove_matrix(&A);
  s21_remove_matrix(&R);
  s21_remove_matrix(&Z);
}
END_TEST

START_TEST(test_s21_mult_matrix) {
  matrix_t A, B, R, Z;
  s21_create_matrix(1, 2, &A);
  s21_create_matrix(2, 2, &B);
  s21_create_matrix(1, 2, &R);

  A.matrix[0][0] = 90.56711652816495;
  A.matrix[0][1] = 7.664389277391322;

  B.matrix[0][0] = 48.261763544430636;
  B.matrix[0][1] = -73.6766162164931;
  B.matrix[1][0] = 81.33785819592393;
  B.matrix[1][1] = -37.97769763356647;

  R.matrix[0][0] = 4994.333770986007;
  R.matrix[0][1] = -6963.754544802735;

  int res = s21_mult_matrix(&A, &B, &Z);
  ck_assert_int_eq(res, 0);
  int qqq = s21_eq_matrix(&R, &Z);
  ck_assert_int_eq(qqq, 1);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&R);
  s21_remove_matrix(&Z);
}
END_TEST

START_TEST(test_s21_transpose) {
  matrix_t A, R, REZ;
  s21_create_matrix(2, 1, &A);
  s21_create_matrix(1, 2, &REZ);
  A.matrix[0][0] = 39.445589;
  A.matrix[1][0] = 45.244559;
  REZ.matrix[0][0] = 39.445589;
  REZ.matrix[0][1] = 45.244559;
  int ret = s21_transpose(&A, &R);
  ck_assert_int_eq(ret, 0);
  int qqq = s21_eq_matrix(&R, &REZ);
  ck_assert_int_eq(qqq, 1);
  s21_remove_matrix(&A);
  s21_remove_matrix(&R);
  s21_remove_matrix(&REZ);
}
END_TEST

START_TEST(test_s21_determinant) {
  matrix_t A;
  double r = 0.0;
  s21_create_matrix(3, 3, &A);
  A.matrix[0][0] = 12.846474957868395;
  A.matrix[0][1] = -38.60197731882359;
  A.matrix[0][2] = 97.84236974240218;
  A.matrix[1][0] = -80.64046008920906;
  A.matrix[1][1] = 94.38869328233113;
  A.matrix[1][2] = -56.547599254317866;
  A.matrix[2][0] = -32.39695675714806;
  A.matrix[2][1] = 41.77062384890857;
  A.matrix[2][2] = -30.60493963201266;
  int res = s21_determinant(&A, &r);
  ck_assert_int_eq(res, 0);
  ck_assert(fabs(r - (-12594.429857733581)) < EPSILON);
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(test_s21_calc_complements) {
  matrix_t A, R, new_mat;
  s21_create_matrix(3, 3, &A);
  s21_create_matrix(3, 3, &R);
  A.matrix[0][0] = 25.91697506083412;
  A.matrix[0][1] = 36.91059796583082;
  A.matrix[0][2] = -74.51476406527999;
  A.matrix[1][0] = 74.31657215486891;
  A.matrix[1][1] = -90.45570022797631;
  A.matrix[1][2] = 27.273735358710894;
  A.matrix[2][0] = 63.201868292687436;
  A.matrix[2][1] = 16.634280168535952;
  A.matrix[2][2] = 90.73538931348031;
  // expected result
  R.matrix[0][0] = -8661.21213100821;
  R.matrix[0][1] = -5019.392076924527;
  R.matrix[0][2] = 6953.171934520688;
  R.matrix[1][0] = -4588.59693837724;
  R.matrix[1][1] = 7061.059126287055;
  R.matrix[1][2] = 1901.7085269579036;
  R.matrix[2][0] = -5733.595279995511;
  R.matrix[2][1] = -6244.5345593679185;
  R.matrix[2][2] = -5087.407243925776;
  int res = s21_calc_complements(&A, &new_mat);
  ck_assert_int_eq(res, 0);
  int ret = s21_eq_matrix(&R, &new_mat);
  ck_assert_int_eq(ret, 1);
  s21_remove_matrix(&A);
  s21_remove_matrix(&R);
  s21_remove_matrix(&new_mat);
}
END_TEST

START_TEST(test_s21_inverse_matrix) {
  matrix_t A, R, Z;
  s21_create_matrix(4, 4, &A);
  s21_create_matrix(4, 4, &R);
  A.matrix[0][0] = 90.78791276979985;
  A.matrix[0][1] = 24.61855600925972;
  A.matrix[0][2] = -90.38196354509769;
  A.matrix[0][3] = 15.60012882811894;
  A.matrix[1][0] = 21.947299432327227;
  A.matrix[1][1] = 33.687626143889275;
  A.matrix[1][2] = -42.79465277978321;
  A.matrix[1][3] = -66.6357221028638;
  A.matrix[2][0] = 63.51425889594381;
  A.matrix[2][1] = -4.822502209046846;
  A.matrix[2][2] = 73.2338208318034;
  A.matrix[2][3] = 12.82996510477733;
  A.matrix[3][0] = 11.482300610138893;
  A.matrix[3][1] = 92.5176452462731;
  A.matrix[3][2] = -48.12318633935904;
  A.matrix[3][3] = 82.80068402149985;
  // rez
  R.matrix[0][0] = 0.006112;
  R.matrix[0][1] = 0.000834;
  R.matrix[0][2] = 0.007002;
  R.matrix[0][3] = -0.001565;
  R.matrix[1][0] = -0.006441;
  R.matrix[1][1] = 0.010384;
  R.matrix[1][2] = 0.004000;
  R.matrix[1][3] = 0.008950;
  R.matrix[2][0] = -0.006206;
  R.matrix[2][1] = 0.001827;
  R.matrix[2][2] = 0.007985;
  R.matrix[2][3] = 0.001402;
  R.matrix[3][0] = 0.002742;
  R.matrix[3][1] = -0.010656;
  R.matrix[3][2] = -0.000800;
  R.matrix[3][3] = 0.003109;
  s21_print_matrix(R);
  int res = s21_inverse_matrix(&A, &Z);
  ck_assert_int_eq(res, 0);
  int ret = s21_eq_matrix(&Z, &R);
  ck_assert_int_eq(ret, 1);
  s21_remove_matrix(&A);
  s21_remove_matrix(&R);
  s21_remove_matrix(&Z);
}
END_TEST

Suite *s21_matrix_suite() {
  Suite *s = suite_create("s21_matrix_test");

  TCase *tc_s21_create_matrix = tcase_create("test_s21_create_matrix");
  suite_add_tcase(s, tc_s21_create_matrix);
  tcase_add_test(tc_s21_create_matrix, test_s21_create_matrix);

  TCase *tc_s21_eq_matrix = tcase_create("test_s21_eq_matrix");
  suite_add_tcase(s, tc_s21_eq_matrix);
  tcase_add_test(tc_s21_eq_matrix, test_s21_eq_matrix);

  TCase *tc_s21_sum_matrix = tcase_create("test_s21_sum_matrix");
  suite_add_tcase(s, tc_s21_sum_matrix);
  tcase_add_test(tc_s21_sum_matrix, test_s21_sum_matrix);

  TCase *tc_s21_sub_matrix = tcase_create("test_s21_sub_matrix");
  suite_add_tcase(s, tc_s21_sub_matrix);
  tcase_add_test(tc_s21_sub_matrix, test_s21_sub_matrix);

  TCase *tc_s21_mult_number = tcase_create("test_s21_mult_number");
  suite_add_tcase(s, tc_s21_mult_number);
  tcase_add_test(tc_s21_mult_number, test_s21_mult_number);

  TCase *tc_s21_mult_matrix = tcase_create("test_s21_mult_matrix");
  suite_add_tcase(s, tc_s21_mult_matrix);
  tcase_add_test(tc_s21_mult_matrix, test_s21_mult_matrix);

  TCase *tc_s21_transpose = tcase_create("test_s21_transpose");
  suite_add_tcase(s, tc_s21_transpose);
  tcase_add_test(tc_s21_transpose, test_s21_transpose);

  TCase *tc_s21_determinant = tcase_create("test_s21_determinant");
  suite_add_tcase(s, tc_s21_determinant);
  tcase_add_test(tc_s21_determinant, test_s21_determinant);

  TCase *tc_s21_calc_complements = tcase_create("test_s21_calc_complements");
  suite_add_tcase(s, tc_s21_calc_complements);
  tcase_add_test(tc_s21_calc_complements, test_s21_calc_complements);

  TCase *tc_s21_inverse_matrix = tcase_create("test_s21_inverse_matrix");
  suite_add_tcase(s, tc_s21_inverse_matrix);
  tcase_add_test(tc_s21_inverse_matrix, test_s21_inverse_matrix);

  return s;
}

int main() {
  int no_failed = 0;

  Suite *s = s21_matrix_suite();

  SRunner *runner = srunner_create(s);

  srunner_run_all(runner, CK_NORMAL);
  no_failed = srunner_ntests_failed(runner);
  srunner_free(runner);

  return (no_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}

void s21_print_matrix(matrix_t matrix) {
  for (int i = 0; i < matrix.rows; i++) {
    for (int j = 0; j < matrix.columns; j++) {
      printf("%s%6lf%s ", GREEN, matrix.matrix[i][j], RESET);
    }
    printf("\n");
  }
}
