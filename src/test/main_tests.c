/*
 * DO NOT EDIT THIS FILE. Generated by checkmk.
 * Edit the original source file "test.check" instead.
 */

#include <check.h>

#include <gmp.h>

START_TEST(add_1)
{
int a = 5;
int b = 10;
ck_assert_int_eq(15, (a + b));


}
END_TEST

int main(void)
{
    Suite *s1 = suite_create("Core");
    TCase *tc1_1 = tcase_create("Core");
    SRunner *sr = srunner_create(s1);
    int nf;

    suite_add_tcase(s1, tc1_1);
    tcase_add_test(tc1_1, add_1);

    srunner_run_all(sr, CK_ENV);
    nf = srunner_ntests_failed(sr);
    srunner_free(sr);

    return nf == 0 ? 0 : 1;
}
