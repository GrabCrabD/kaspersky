#include <check.h>
#include <stdio.h>
#include <stdlib.h>

#include "s21_matrix.h"

int n = 3, m = 2, max = 5;
// int n = 1, m = 1, max = 5;

START_TEST(create_matrix) {
  matrix_t a, b, r;
  a.matrix = NULL;
  b.matrix = NULL;
  r.matrix = NULL;

  //  ERROR

  ck_assert_int_eq(1, s21_create_matrix(-3, 0, &a));
  ck_assert_int_eq(1, s21_create_matrix(-1, -2, &b));
  ck_assert_int_eq(1, s21_create_matrix(0, -2, &r));

  ck_assert_int_eq(1, s21_create_matrix(n, 0, &a));
  ck_assert_int_eq(1, s21_create_matrix(0, m, &b));
  ck_assert_int_eq(1, s21_create_matrix(0, n, &r));

  matrix_t *err = NULL;
  ck_assert_int_eq(1, s21_create_matrix(n, m, err));

  //  OK

  ck_assert_int_eq(0, s21_create_matrix(max, n, &a));
  ck_assert_int_eq(0, s21_create_matrix(m, max, &b));
  ck_assert_int_eq(0, s21_create_matrix(max, max, &r));

  ck_assert_int_eq(0, s21_create_matrix(n, m, &a));
  ck_assert_int_eq(0, s21_create_matrix(n, m, &b));
  ck_assert_int_eq(0, s21_create_matrix(n, m, &r));

  ck_assert_int_eq(0, s21_create_matrix(n, m, &a));
  ck_assert_int_eq(0, s21_create_matrix(m, n, &b));
  ck_assert_int_eq(0, s21_create_matrix(n + m, n + m, &r));

  ck_assert_int_eq(0, s21_create_matrix(n, n, &a));
  ck_assert_int_eq(0, s21_create_matrix(m, m, &b));
  ck_assert_int_eq(0, s21_create_matrix(n * m, n * m, &r));

  s21_remove_matrix(&a);
  s21_remove_matrix(&b);
  s21_remove_matrix(&r);
}
END_TEST

START_TEST(remove_matrix) {
  matrix_t a, b, r;
  a.matrix = NULL;
  b.matrix = NULL;
  r.matrix = NULL;

  //  ERROR

  ck_assert_int_eq(1, s21_create_matrix(0, 0, &a));
  ck_assert_int_eq(1, s21_create_matrix(-1, -2, &b));
  ck_assert_int_eq(1, s21_create_matrix(0, -2, &r));

  s21_remove_matrix(&a);
  s21_remove_matrix(&b);
  s21_remove_matrix(&r);
  ck_assert_int_eq(1, (a.matrix == NULL));
  ck_assert_int_eq(1, (b.matrix == NULL));
  ck_assert_int_eq(1, (r.matrix == NULL));

  ck_assert_int_eq(1, s21_create_matrix(n, 0, &a));
  ck_assert_int_eq(1, s21_create_matrix(0, m, &b));
  ck_assert_int_eq(1, s21_create_matrix(0, -n, &r));

  s21_remove_matrix(&a);
  s21_remove_matrix(&b);
  s21_remove_matrix(&r);
  ck_assert_int_eq(1, (a.matrix == NULL));
  ck_assert_int_eq(1, (b.matrix == NULL));
  ck_assert_int_eq(1, (r.matrix == NULL));

  matrix_t *err = NULL;
  s21_remove_matrix(err);
  ck_assert_int_eq(1, (err == NULL));

  //  OK

  ck_assert_int_eq(0, s21_create_matrix(n, m, &a));
  ck_assert_int_eq(0, s21_create_matrix(n, m, &b));
  ck_assert_int_eq(0, s21_create_matrix(n, m, &r));

  s21_remove_matrix(&a);
  s21_remove_matrix(&b);
  s21_remove_matrix(&r);
  ck_assert_int_eq(1, (a.matrix == NULL));
  ck_assert_int_eq(1, (b.matrix == NULL));
  ck_assert_int_eq(1, (r.matrix == NULL));

  ck_assert_int_eq(0, s21_create_matrix(n, m, &a));
  ck_assert_int_eq(0, s21_create_matrix(m, n, &b));
  ck_assert_int_eq(0, s21_create_matrix(n + m, n + m, &r));

  s21_remove_matrix(&a);
  s21_remove_matrix(&b);
  s21_remove_matrix(&r);
  ck_assert_int_eq(1, (a.matrix == NULL));
  ck_assert_int_eq(1, (b.matrix == NULL));
  ck_assert_int_eq(1, (r.matrix == NULL));

  ck_assert_int_eq(0, s21_create_matrix(n, n, &a));
  ck_assert_int_eq(0, s21_create_matrix(m, m, &b));
  ck_assert_int_eq(0, s21_create_matrix(n * m, n * m, &r));

  s21_remove_matrix(&a);
  s21_remove_matrix(&b);
  s21_remove_matrix(&r);
  ck_assert_int_eq(1, (a.matrix == NULL));
  ck_assert_int_eq(1, (b.matrix == NULL));
  ck_assert_int_eq(1, (r.matrix == NULL));

  s21_remove_matrix(&a);
  s21_remove_matrix(&b);
  s21_remove_matrix(&r);
}
END_TEST

START_TEST(eq_matrix) {
  matrix_t a, b, r;
  matrix_t *err = NULL;
  a.matrix = NULL;
  b.matrix = NULL;
  r.matrix = NULL;

  ck_assert_int_eq(0, s21_eq_matrix(&a, err));
  ck_assert_int_eq(0, s21_eq_matrix(err, &b));
  ck_assert_int_eq(0, s21_eq_matrix(err, err));

  ck_assert_int_eq(0, s21_eq_matrix(&a, &a));
  copy(&b, &a);
  ck_assert_int_eq(0, s21_eq_matrix(&b, &b));
  copy(err, &a);
  ck_assert_int_eq(0, s21_eq_matrix(&b, &b));
  ck_assert_int_eq(0, s21_eq_matrix(&r, &r));

  s21_create_matrix(n, m, &a);
  ck_assert_int_eq(0, s21_eq_matrix(&a, &b));
  ck_assert_int_eq(0, s21_eq_matrix(&a, &r));
  s21_create_matrix(n, n, &b);
  s21_create_matrix(m, m, &r);

  ck_assert_int_eq(1, s21_eq_matrix(&a, &a));
  ck_assert_int_eq(1, s21_eq_matrix(&b, &b));
  ck_assert_int_eq(1, s21_eq_matrix(&r, &r));
  r.matrix[0][0] = 1.234567;
  ck_assert_int_eq(1, s21_eq_matrix(&r, &r));

  ck_assert_int_eq(0, s21_eq_matrix(&a, err));
  ck_assert_int_eq(0, s21_eq_matrix(err, &b));
  ck_assert_int_eq(0, s21_eq_matrix(err, err));

  ck_assert_int_eq(0, s21_eq_matrix(&a, &b));
  ck_assert_int_eq(0, s21_eq_matrix(&a, &r));
  ck_assert_int_eq(0, s21_eq_matrix(&b, &a));
  ck_assert_int_eq(0, s21_eq_matrix(&b, &r));
  ck_assert_int_eq(0, s21_eq_matrix(&r, &a));
  ck_assert_int_eq(0, s21_eq_matrix(&r, &b));
  copy(&r, &a);
  r.matrix[0][0] = 1.123456;
  ck_assert_int_eq(0, s21_eq_matrix(&a, &r));

  s21_remove_matrix(&a);
  s21_remove_matrix(&b);
  s21_remove_matrix(&r);
}
END_TEST

START_TEST(sum_matrix) {
  matrix_t a, b, r, c, d;
  matrix_t *err = NULL;
  a.matrix = NULL;
  b.matrix = NULL;
  r.matrix = NULL;
  c.matrix = NULL;
  d.matrix = NULL;

  ck_assert_int_eq(1, s21_sum_matrix(&a, err, &r));
  ck_assert_int_eq(1, s21_sum_matrix(err, &a, &r));
  ck_assert_int_eq(1, s21_sum_matrix(err, err, &r));
  ck_assert_int_eq(1, s21_sum_matrix(&a, &a, &r));

  s21_create_matrix(n, m, &a);
  ck_assert_int_eq(1, s21_sum_matrix(&a, &c, &r));
  ck_assert_int_eq(1, s21_sum_matrix(&c, &a, &r));
  ck_assert_int_eq(1, s21_sum_matrix(&a, &d, &r));
  ck_assert_int_eq(1, s21_sum_matrix(&d, &a, &r));
  s21_create_matrix(n, m, &b);
  s21_create_matrix(n, m, &r);
  s21_create_matrix(m, m, &c);
  s21_create_matrix(n, n, &d);

  ck_assert_int_eq(1, s21_sum_matrix(&a, err, &r));
  ck_assert_int_eq(1, s21_sum_matrix(err, &a, &r));
  ck_assert_int_eq(1, s21_sum_matrix(err, err, &r));

  ck_assert_int_eq(1, s21_sum_matrix(&a, &c, &r));
  ck_assert_int_eq(1, s21_sum_matrix(&c, &a, &r));
  ck_assert_int_eq(1, s21_sum_matrix(&a, &d, &r));
  ck_assert_int_eq(1, s21_sum_matrix(&d, &a, &r));
  ck_assert_int_eq(1, s21_sum_matrix(&d, &c, &r));
  ck_assert_int_eq(1, s21_sum_matrix(&c, &d, &r));

  ck_assert_int_eq(0, s21_sum_matrix(&a, &b, &r));
  ck_assert_int_eq(0, s21_sum_matrix(&b, &a, &r));

  s21_remove_matrix(&a);
  s21_remove_matrix(&b);
  s21_remove_matrix(&r);
  s21_remove_matrix(&c);
  s21_remove_matrix(&d);
}
END_TEST

START_TEST(sub_matrix) {
  matrix_t a, b, r, c, d;
  matrix_t *err = NULL;
  a.matrix = NULL;
  b.matrix = NULL;
  r.matrix = NULL;
  c.matrix = NULL;
  d.matrix = NULL;

  ck_assert_int_eq(1, s21_sub_matrix(&a, err, &r));
  ck_assert_int_eq(1, s21_sub_matrix(err, &a, &r));
  ck_assert_int_eq(1, s21_sub_matrix(err, err, &r));
  ck_assert_int_eq(1, s21_sub_matrix(&a, &a, &r));

  s21_create_matrix(n, m, &a);
  ck_assert_int_eq(1, s21_sub_matrix(&a, &c, &r));
  ck_assert_int_eq(1, s21_sub_matrix(&c, &a, &r));
  ck_assert_int_eq(1, s21_sub_matrix(&a, &d, &r));
  ck_assert_int_eq(1, s21_sub_matrix(&d, &a, &r));
  s21_create_matrix(n, m, &b);
  s21_create_matrix(n, m, &r);
  s21_create_matrix(m, m, &c);
  s21_create_matrix(n, n, &d);

  ck_assert_int_eq(1, s21_sub_matrix(&a, err, &r));
  ck_assert_int_eq(1, s21_sub_matrix(err, &a, &r));
  ck_assert_int_eq(1, s21_sub_matrix(err, err, &r));

  ck_assert_int_eq(1, s21_sub_matrix(&a, &c, &r));
  ck_assert_int_eq(1, s21_sub_matrix(&c, &a, &r));
  ck_assert_int_eq(1, s21_sub_matrix(&a, &d, &r));
  ck_assert_int_eq(1, s21_sub_matrix(&d, &a, &r));
  ck_assert_int_eq(1, s21_sub_matrix(&d, &c, &r));
  ck_assert_int_eq(1, s21_sub_matrix(&c, &d, &r));

  ck_assert_int_eq(0, s21_sub_matrix(&a, &b, &r));
  ck_assert_int_eq(0, s21_sub_matrix(&b, &a, &r));

  s21_remove_matrix(&a);
  s21_remove_matrix(&b);
  s21_remove_matrix(&r);
  s21_remove_matrix(&c);
  s21_remove_matrix(&d);
}
END_TEST

START_TEST(mult_number) {
  matrix_t a, b, r;
  matrix_t *err = NULL;
  double num = 0.;
  a.matrix = NULL;
  b.matrix = NULL;
  r.matrix = NULL;

  ck_assert_int_eq(1, s21_mult_number(&a, num, &r));
  ck_assert_int_eq(1, s21_mult_number(err, num, &r));

  s21_create_matrix(n, m, &a);
  s21_create_matrix(n, n, &b);
  s21_create_matrix(max, max, &r);

  for (int i = 0; i < n; i++) b.matrix[i][i] = 2.;

  ck_assert_int_eq(0, s21_mult_number(&a, num, &r));
  ck_assert_int_eq(0, s21_mult_number(&b, num, &r));
  ck_assert_int_eq(0, s21_mult_number(&r, num, &r));

  s21_remove_matrix(&a);
  s21_remove_matrix(&b);
  s21_remove_matrix(&r);
}
END_TEST

START_TEST(mult_matrix) {
  matrix_t a, b, r, c, d;
  matrix_t *err = NULL;
  a.matrix = NULL;
  b.matrix = NULL;
  r.matrix = NULL;
  c.matrix = NULL;
  d.matrix = NULL;

  ck_assert_int_eq(1, s21_mult_matrix(&a, err, &r));
  ck_assert_int_eq(1, s21_mult_matrix(err, &a, &r));
  ck_assert_int_eq(1, s21_mult_matrix(err, err, &r));
  ck_assert_int_eq(1, s21_mult_matrix(&a, &a, &r));

  s21_create_matrix(n, m, &a);
  ck_assert_int_eq(1, s21_mult_matrix(&a, &c, &r));
  ck_assert_int_eq(1, s21_mult_matrix(&c, &a, &r));
  s21_create_matrix(m, n, &b);
  s21_create_matrix(n, m, &r);
  s21_create_matrix(m, m, &c);
  s21_create_matrix(n, n, &d);

  ck_assert_int_eq(1, s21_mult_matrix(&a, err, &r));
  ck_assert_int_eq(1, s21_mult_matrix(err, &a, &r));
  ck_assert_int_eq(1, s21_mult_matrix(err, err, &r));

  ck_assert_int_eq(0, s21_mult_matrix(&a, &c, &r));
  ck_assert_int_eq(1, s21_mult_matrix(&c, &a, &r));
  ck_assert_int_eq(1, s21_mult_matrix(&a, &d, &r));
  ck_assert_int_eq(0, s21_mult_matrix(&d, &a, &r));
  ck_assert_int_eq(1, s21_mult_matrix(&d, &c, &r));
  ck_assert_int_eq(1, s21_mult_matrix(&c, &d, &r));

  ck_assert_int_eq(0, s21_mult_matrix(&a, &b, &r));  //
  ck_assert_int_eq(0, s21_mult_matrix(&b, &a, &r));

  s21_remove_matrix(&a);
  s21_remove_matrix(&b);
  s21_remove_matrix(&r);
  s21_remove_matrix(&c);
  s21_remove_matrix(&d);
}
END_TEST

START_TEST(transpose) {
  matrix_t a, b, r;
  matrix_t *err = NULL;
  a.matrix = NULL;
  b.matrix = NULL;
  r.matrix = NULL;

  ck_assert_int_eq(1, s21_transpose(&a, err));
  ck_assert_int_eq(1, s21_transpose(err, &b));
  ck_assert_int_eq(1, s21_transpose(err, err));

  ck_assert_int_eq(1, s21_transpose(&a, &a));
  copy(&b, &a);
  ck_assert_int_eq(1, s21_transpose(&b, &b));
  copy(err, &a);
  ck_assert_int_eq(1, s21_transpose(&b, &b));
  ck_assert_int_eq(1, s21_transpose(&r, &r));

  s21_create_matrix(n, m, &a);
  ck_assert_int_eq(0, s21_transpose(&a, &b));
  ck_assert_int_eq(0, s21_transpose(&a, &r));
  s21_create_matrix(n, n, &b);
  s21_create_matrix(m, m, &r);

  ck_assert_int_eq(0, s21_transpose(&r, &r));

  ck_assert_int_eq(1, s21_transpose(&a, err));
  ck_assert_int_eq(1, s21_transpose(err, &b));
  ck_assert_int_eq(1, s21_transpose(err, err));

  ck_assert_int_eq(0, s21_transpose(&a, &b));
  ck_assert_int_eq(0, s21_transpose(&a, &r));
  ck_assert_int_eq(0, s21_transpose(&b, &a));
  ck_assert_int_eq(0, s21_transpose(&b, &r));
  ck_assert_int_eq(0, s21_transpose(&r, &a));
  ck_assert_int_eq(0, s21_transpose(&r, &b));

  s21_remove_matrix(&a);
  s21_remove_matrix(&b);
  s21_remove_matrix(&r);
}
END_TEST

START_TEST(calc_complements) {
  matrix_t a, b, r;
  matrix_t *err = NULL;
  a.matrix = NULL;
  b.matrix = NULL;
  r.matrix = NULL;

  ck_assert_int_eq(1, s21_calc_complements(&a, err));
  ck_assert_int_eq(1, s21_calc_complements(err, &b));
  ck_assert_int_eq(1, s21_calc_complements(err, err));

  ck_assert_int_eq(1, s21_calc_complements(&a, &a));
  copy(&b, &a);
  ck_assert_int_eq(1, s21_calc_complements(&b, &b));
  copy(err, &a);
  ck_assert_int_eq(1, s21_calc_complements(&b, &b));
  ck_assert_int_eq(1, s21_calc_complements(&r, &r));

  s21_create_matrix(n, m, &a);
  ck_assert_int_eq(1, s21_calc_complements(&a, &b));
  ck_assert_int_eq(1, s21_calc_complements(&a, &r));
  s21_create_matrix(n, n, &b);
  s21_create_matrix(m, m, &r);

  ck_assert_int_eq(0, s21_calc_complements(&r, &r));

  ck_assert_int_eq(1, s21_calc_complements(&a, err));
  ck_assert_int_eq(1, s21_calc_complements(err, &b));
  ck_assert_int_eq(1, s21_calc_complements(err, err));

  ck_assert_int_eq(1, s21_calc_complements(&a, &b));
  ck_assert_int_eq(1, s21_calc_complements(&a, &r));
  ck_assert_int_eq(0, s21_calc_complements(&b, &a));
  ck_assert_int_eq(0, s21_calc_complements(&b, &r));
  ck_assert_int_eq(0, s21_calc_complements(&r, &a));
  ck_assert_int_eq(0, s21_calc_complements(&r, &b));

  for (int i = 0; i < n; i++) b.matrix[i][i] = 2. * i;
  ck_assert_int_eq(0, s21_calc_complements(&b, &a));
  ck_assert_int_eq(0, s21_calc_complements(&b, &r));

  s21_remove_matrix(&a);
  s21_remove_matrix(&b);
  s21_remove_matrix(&r);
}
END_TEST

START_TEST(determinant) {
  matrix_t a, b, r;
  matrix_t *err = NULL;
  double num = 0.;
  double *er_num = NULL;
  a.matrix = NULL;
  b.matrix = NULL;
  r.matrix = NULL;

  ck_assert_int_eq(1, s21_determinant(&a, er_num));
  ck_assert_int_eq(1, s21_determinant(err, er_num));

  ck_assert_int_eq(1, s21_determinant(&a, &num));
  ck_assert_int_eq(1, s21_determinant(err, &num));

  s21_create_matrix(n, m, &a);
  s21_create_matrix(n, n, &b);
  s21_create_matrix(max, max, &r);

  ck_assert_int_eq(0, s21_determinant(&r, &num));
  ck_assert_int_eq(1, s21_determinant(&r, er_num));
  ck_assert_int_eq(1, s21_determinant(err, &num));
  ck_assert_int_eq(1, s21_determinant(err, er_num));

  for (int i = 0; i < n; i++) b.matrix[i][i] = 2.;
  ck_assert_int_eq(1, s21_determinant(&a, &num));
  ck_assert_int_eq(1, s21_determinant(&a, er_num));
  ck_assert_int_eq(0, s21_determinant(&b, &num));
  ck_assert_int_eq(1, s21_determinant(&b, er_num));
  ck_assert_int_eq(0, s21_determinant(&r, &num));
  ck_assert_int_eq(1, s21_determinant(&r, er_num));

  r.rows = -1;
  r.columns = -1;
  ck_assert_int_eq(1, s21_determinant(&r, &num));
  r.rows = max;
  r.columns = max;

  s21_remove_matrix(&a);
  s21_remove_matrix(&b);
  s21_remove_matrix(&r);
}
END_TEST

START_TEST(inverse_matrix) {
  matrix_t a, b, r;
  matrix_t *err = NULL;
  a.matrix = NULL;
  b.matrix = NULL;
  r.matrix = NULL;

  ck_assert_int_eq(1, s21_inverse_matrix(&a, err));
  ck_assert_int_eq(1, s21_inverse_matrix(err, &b));
  ck_assert_int_eq(1, s21_inverse_matrix(err, err));

  ck_assert_int_eq(1, s21_inverse_matrix(&a, &a));
  copy(&b, &a);
  ck_assert_int_eq(1, s21_inverse_matrix(&b, &b));
  copy(err, &a);
  ck_assert_int_eq(1, s21_inverse_matrix(&b, &b));
  ck_assert_int_eq(1, s21_inverse_matrix(&r, &r));

  s21_create_matrix(n, m, &a);
  ck_assert_int_eq(1, s21_inverse_matrix(&a, &b));
  ck_assert_int_eq(1, s21_inverse_matrix(&a, &r));
  s21_create_matrix(n, n, &b);
  s21_create_matrix(m, m, &r);

  ck_assert_int_eq(2, s21_inverse_matrix(&r, &r));

  ck_assert_int_eq(1, s21_inverse_matrix(&a, err));
  ck_assert_int_eq(1, s21_inverse_matrix(err, &b));
  ck_assert_int_eq(1, s21_inverse_matrix(err, err));

  for (int i = 0; i < n; i++) b.matrix[i][i] = 2.;
  ck_assert_int_eq(1, s21_inverse_matrix(&a, &b));
  ck_assert_int_eq(1, s21_inverse_matrix(&a, &r));
  ck_assert_int_eq(0, s21_inverse_matrix(&b, &a));
  ck_assert_int_eq(0, s21_inverse_matrix(&b, &r));
  ck_assert_int_eq(0, s21_inverse_matrix(&r, &a));
  ck_assert_int_eq(0, s21_inverse_matrix(&r, &b));

  ck_assert_int_eq(0, s21_inverse_matrix(&b, &a));
  ck_assert_int_eq(0, s21_inverse_matrix(&b, &r));

  s21_remove_matrix(&a);
  s21_remove_matrix(&b);
  s21_remove_matrix(&r);
}
END_TEST

Suite *matrix_suite(void) {
  Suite *s = suite_create("matrix_testcase");
  TCase *tc_matrix = tcase_create("Core");

  suite_add_tcase(s, tc_matrix);
  tcase_add_test(tc_matrix, create_matrix);
  tcase_add_test(tc_matrix, remove_matrix);
  tcase_add_test(tc_matrix, eq_matrix);
  tcase_add_test(tc_matrix, sum_matrix);
  tcase_add_test(tc_matrix, sub_matrix);
  tcase_add_test(tc_matrix, mult_number);
  tcase_add_test(tc_matrix, mult_matrix);
  tcase_add_test(tc_matrix, transpose);
  tcase_add_test(tc_matrix, calc_complements);
  tcase_add_test(tc_matrix, determinant);
  tcase_add_test(tc_matrix, inverse_matrix);

  return s;
}

int main() {
  int number_failed;
  Suite *s;
  SRunner *sr;

  s = matrix_suite();
  sr = srunner_create(s);

  srunner_set_fork_status(sr, CK_NOFORK);
  srunner_run_all(sr, CK_NORMAL);
  number_failed = srunner_ntests_failed(sr);
  srunner_free(sr);
  return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}