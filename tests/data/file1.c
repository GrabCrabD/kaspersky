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

Suite *matrix_suite(void) {
  Suite *s = suite_create("matrix_testcase");
  TCase *tc_matrix = tcase_create("Core");

  suite_add_tcase(s, tc_matrix);
  tcase_add_test(tc_matrix, create_matrix);
  tcase_add_test(tc_matrix, remove_matrix);
  tcase_add_test(tc_matrix, eq_matrix);
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
