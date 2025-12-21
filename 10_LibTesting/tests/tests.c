#include <check.h>
#include "buf.h"

START_TEST(test_init) {
    float *a = 0;

    ck_assert_uint_eq(buf_capacity(a), 0); /* capacity init */
    ck_assert_uint_eq(buf_size(a), 0); /* size init */

    buf_push(a, 1.3f);
    ck_assert_uint_eq(buf_size(a), 1); /* size 1 */
    ck_assert_float_eq(a[0], 1.3f); /* value */

    buf_clear(a);
    ck_assert_uint_eq(buf_size(a), 0); /* clear */
    ck_assert_ptr_nonnull(a); /* clear not-free */

    buf_free(a);
    ck_assert_ptr_null(a); /* free */

    buf_clear(a);
    ck_assert_uint_eq(buf_size(a), 0); /* clear empty */
    ck_assert_ptr_null(a); /* clear no-op */
}
END_TEST

START_TEST(test_push) {
    long *ai = 0;

    for (int i = 0; i < 10000; i++)
        buf_push(ai, i);
    ck_assert_uint_eq(buf_size(ai), 10000); /* size 10000 */

    int match = 0;
    for (int i = 0; i < (int)(buf_size(ai)); i++)
        match += ai[i] == i;
    ck_assert_int_eq(match, 10000); /* match 10000 */
    buf_free(ai);
}
END_TEST

START_TEST(test_grow) {
    long *ai = 0;

    buf_grow(ai, 1000);
    ck_assert_uint_eq(buf_capacity(ai), 1000); /* grow 1000 */
    ck_assert_uint_eq(buf_size(ai), 0); /* size 0 (grow) */

    buf_trunc(ai, 100);
    ck_assert_uint_eq(buf_capacity(ai), 100); /* trunc 100 */
    buf_free(ai);
}
END_TEST

START_TEST(test_pop) {
    float *a = 0;

    buf_push(a, 1.1f);
    buf_push(a, 1.2f);
    buf_push(a, 1.3f);
    buf_push(a, 1.4f);
    ck_assert_uint_eq(buf_size(a), 4); /* size 4 */
    ck_assert_float_eq(buf_pop(a), 1.4f); /* pop 3 */

    buf_trunc(a, 3);
    ck_assert_uint_eq(buf_size(a), 3); /* size 3 */
    ck_assert_float_eq(buf_pop(a), 1.3f); /* pop 2 */
    ck_assert_float_eq(buf_pop(a), 1.2f); /* pop 1 */
    ck_assert_float_eq(buf_pop(a), 1.1f); /* pop 0 */
    ck_assert_uint_eq(buf_size(a), 0); /* size 0 (pop) */
    buf_free(a);
}
END_TEST

int main(void) {
    TCase *tcase_init, *tcase_push, *tcase_grow, *tcase_pop;
    Suite *suite;
    SRunner *runner;
    int failed_count;

    tcase_init = tcase_create("test_init");
    tcase_push = tcase_create("test_push");
    tcase_grow = tcase_create("test_grow");
    tcase_pop = tcase_create("test_pop");

    tcase_add_test(tcase_init, test_init);
    tcase_add_test(tcase_push, test_push);
    tcase_add_test(tcase_grow, test_grow);
    tcase_add_test(tcase_pop, test_pop);

    suite = suite_create("buf");
    suite_add_tcase(suite, tcase_init);
    suite_add_tcase(suite, tcase_push);
    suite_add_tcase(suite, tcase_grow);
    suite_add_tcase(suite, tcase_pop);

    runner = srunner_create(suite);
    srunner_run_all(runner, CK_VERBOSE);
    failed_count = srunner_ntests_failed(runner);
    srunner_free(runner);

    return failed_count != 0;
}
