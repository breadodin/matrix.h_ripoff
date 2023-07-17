#ifndef S21_MATRIX_H
#define S21_MATRIX_H
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SUCCESS 1
#define FAILURE 0
#define EPSILON 1e-6
#define EXIST 0
#define NOT_EXIST 1
#define OK 0
#define INCOMPATIBLE 2

typedef struct matrix_struct {
  double **matrix;
  int rows;
  int columns;
  bool initialized;
} matrix_t;

int s21_create_matrix(int rows, int columns, matrix_t *result);
int s21_eq_matrix(matrix_t *matrix_one, matrix_t *matrix_two);
int s21_sum_matrix(matrix_t *A, matrix_t *B, matrix_t *result);
int s21_sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result);
int s21_mult_number(matrix_t *A, double number, matrix_t *result);
int s21_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result);
int s21_transpose(matrix_t *A, matrix_t *result);
int s21_calc_complements(matrix_t *A, matrix_t *result);
int s21_determinant(matrix_t *A, double *result);
int s21_inverse_matrix(matrix_t *A, matrix_t *result);
void s21_remove_matrix(matrix_t *matrix);
//  extra functions
int s21_matrix_exist(matrix_t matrix);
void s21_print_matrix(matrix_t matrix);
//  sub functions
int algebraic_expressions(matrix_t *A, matrix_t *result);
int calc_minor(int row, int column, matrix_t *A, matrix_t *result);
void sub_mult_number(matrix_t *A, double number, matrix_t *result);
void sub_determinant(matrix_t *A, matrix_t *T, matrix_t *O, int r, double p);
#endif  // S21_MATRIX_H
