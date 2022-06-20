#include <stdio.h>
#include <stdlib.h>
#include <check.h>

void test_cat();

#define TEST_CAT(STRING)                                                                    \
    {                                                                                       \
        system("./s21_"STRING" >1");                                                        \
        system(STRING" >2");                                                                \
        system("xxd 1 >1.hex");                                                             \
        system("xxd 2 >2.hex");                                                             \
        ck_assert_msg(system("diff -s 1.hex 2.hex >result") == 0, "Failed on: '"STRING"'"); \
    }


START_TEST(s21_cat_test_main_0) {
    TEST_CAT("cat test.txt");
    TEST_CAT("cat -n test.txt");
    TEST_CAT("cat -n test.txt test_cat.c");
    TEST_CAT("cat -v test.txt");
    TEST_CAT("cat -t test.txt");
    TEST_CAT("cat -b test.txt");
    TEST_CAT("cat -e test.txt");
    TEST_CAT("cat -s test.txt");
}
END_TEST

START_TEST(s21_cat_test_multi_p1) {
    TEST_CAT("cat -benst test.txt");
    TEST_CAT("cat -bents test.txt");
    TEST_CAT("cat -besnt test.txt");
    TEST_CAT("cat -bestn test.txt");
    TEST_CAT("cat -betns test.txt");
    TEST_CAT("cat -betsn test.txt");
    TEST_CAT("cat -bnest test.txt");
    TEST_CAT("cat -bnets test.txt");
    TEST_CAT("cat -bnset test.txt");
    TEST_CAT("cat -bnste test.txt");
    TEST_CAT("cat -bntes test.txt");
    TEST_CAT("cat -bntse test.txt");
    TEST_CAT("cat -bsent test.txt");
    TEST_CAT("cat -bsetn test.txt");
    TEST_CAT("cat -bsnet test.txt");
    TEST_CAT("cat -bsnte test.txt");
    TEST_CAT("cat -bsten test.txt");
    TEST_CAT("cat -bstne test.txt");
    TEST_CAT("cat -btens test.txt");
    TEST_CAT("cat -btesn test.txt");
    TEST_CAT("cat -btnes test.txt");
    TEST_CAT("cat -btnse test.txt");
    TEST_CAT("cat -btsen test.txt");
    TEST_CAT("cat -btsne test.txt");
}
END_TEST

START_TEST(s21_cat_test_multi_p2) {
    TEST_CAT("cat -ebnst test.txt");
    TEST_CAT("cat -ebnts test.txt");
    TEST_CAT("cat -ebsnt test.txt");
    TEST_CAT("cat -ebstn test.txt");
    TEST_CAT("cat -ebtns test.txt");
    TEST_CAT("cat -ebtsn test.txt");
    TEST_CAT("cat -enbst test.txt");
    TEST_CAT("cat -enbts test.txt");
    TEST_CAT("cat -ensbt test.txt");
    TEST_CAT("cat -enstb test.txt");
    TEST_CAT("cat -entbs test.txt");
    TEST_CAT("cat -entsb test.txt");
    TEST_CAT("cat -esbnt test.txt");
    TEST_CAT("cat -esbtn test.txt");
    TEST_CAT("cat -esnbt test.txt");
    TEST_CAT("cat -esntb test.txt");
    TEST_CAT("cat -estbn test.txt");
    TEST_CAT("cat -estnb test.txt");
    TEST_CAT("cat -etbns test.txt");
    TEST_CAT("cat -etbsn test.txt");
    TEST_CAT("cat -etnbs test.txt");
    TEST_CAT("cat -etnsb test.txt");
    TEST_CAT("cat -etsbn test.txt");
    TEST_CAT("cat -etsnb test.txt");
}
END_TEST

START_TEST(s21_cat_test_multi_p3) {
    TEST_CAT("cat -nbest test.txt");
    TEST_CAT("cat -nbets test.txt");
    TEST_CAT("cat -nbset test.txt");
    TEST_CAT("cat -nbste test.txt");
    TEST_CAT("cat -nbtes test.txt");
    TEST_CAT("cat -nbtse test.txt");
    TEST_CAT("cat -nebst test.txt");
    TEST_CAT("cat -nebts test.txt");
    TEST_CAT("cat -nesbt test.txt");
    TEST_CAT("cat -nestb test.txt");
    TEST_CAT("cat -netbs test.txt");
    TEST_CAT("cat -netsb test.txt");
    TEST_CAT("cat -nsbet test.txt");
    TEST_CAT("cat -nsbte test.txt");
    TEST_CAT("cat -nsebt test.txt");
    TEST_CAT("cat -nsetb test.txt");
    TEST_CAT("cat -nstbe test.txt");
    TEST_CAT("cat -nsteb test.txt");
    TEST_CAT("cat -ntbes test.txt");
    TEST_CAT("cat -ntbse test.txt");
    TEST_CAT("cat -ntebs test.txt");
    TEST_CAT("cat -ntesb test.txt");
    TEST_CAT("cat -ntsbe test.txt");
    TEST_CAT("cat -ntseb test.txt");
}
END_TEST

START_TEST(s21_cat_test_multi_p4) {
    TEST_CAT("cat -sbent test.txt");
    TEST_CAT("cat -sbetn test.txt");
    TEST_CAT("cat -sbnet test.txt");
    TEST_CAT("cat -sbnte test.txt");
    TEST_CAT("cat -sbten test.txt");
    TEST_CAT("cat -sbtne test.txt");
    TEST_CAT("cat -sebnt test.txt");
    TEST_CAT("cat -sebtn test.txt");
    TEST_CAT("cat -senbt test.txt");
    TEST_CAT("cat -sentb test.txt");
    TEST_CAT("cat -setbn test.txt");
    TEST_CAT("cat -setnb test.txt");
    TEST_CAT("cat -snbet test.txt");
    TEST_CAT("cat -snbte test.txt");
    TEST_CAT("cat -snebt test.txt");
    TEST_CAT("cat -snetb test.txt");
    TEST_CAT("cat -sntbe test.txt");
    TEST_CAT("cat -snteb test.txt");
    TEST_CAT("cat -stben test.txt");
    TEST_CAT("cat -stbne test.txt");
    TEST_CAT("cat -stebn test.txt");
    TEST_CAT("cat -stenb test.txt");
    TEST_CAT("cat -stnbe test.txt");
    TEST_CAT("cat -stneb test.txt");}
END_TEST

START_TEST(s21_cat_test_multi_p5) {
    TEST_CAT("cat -tbens test.txt");
    TEST_CAT("cat -tbesn test.txt");
    TEST_CAT("cat -tbnes test.txt");
    TEST_CAT("cat -tbnse test.txt");
    TEST_CAT("cat -tbsen test.txt");
    TEST_CAT("cat -tbsne test.txt");
    TEST_CAT("cat -tebns test.txt");
    TEST_CAT("cat -tebsn test.txt");
    TEST_CAT("cat -tenbs test.txt");
    TEST_CAT("cat -tensb test.txt");
    TEST_CAT("cat -tesbn test.txt");
    TEST_CAT("cat -tesnb test.txt");
    TEST_CAT("cat -tnbes test.txt");
    TEST_CAT("cat -tnbse test.txt");
    TEST_CAT("cat -tnebs test.txt");
    TEST_CAT("cat -tnesb test.txt");
    TEST_CAT("cat -tnsbe test.txt");
    TEST_CAT("cat -tnseb test.txt");
    TEST_CAT("cat -tsben test.txt");
    TEST_CAT("cat -tsbne test.txt");
    TEST_CAT("cat -tsebn test.txt");
    TEST_CAT("cat -tsenb test.txt");
    TEST_CAT("cat -tsnbe test.txt");
    TEST_CAT("cat -tsneb test.txt");
}
END_TEST


int main(void) {
    Suite *s1 = suite_create("cat_tests");
    SRunner *sr = srunner_create(s1);
    int nf;

    TCase *tc1_1 = tcase_create("s21_cat_test_main_0");
    tcase_add_test(tc1_1, s21_cat_test_main_0);
    suite_add_tcase(s1, tc1_1);

    TCase *tc2_1 = tcase_create("s21_cat_test_1");
    tcase_add_test(tc2_1, s21_cat_test_multi_p1);
    suite_add_tcase(s1, tc2_1);

    TCase *tc3_1 = tcase_create("s21_cat_test_2");
    tcase_add_test(tc3_1, s21_cat_test_multi_p2);
    suite_add_tcase(s1, tc3_1);

    TCase *tc4_1 = tcase_create("s21_cat_test_3");
    tcase_add_test(tc4_1, s21_cat_test_multi_p3);
    suite_add_tcase(s1, tc4_1);

    TCase *tc5_1 = tcase_create("s21_cat_test_4");
    tcase_add_test(tc5_1, s21_cat_test_multi_p4);
    suite_add_tcase(s1, tc5_1);

    TCase *tc6_1 = tcase_create("s21_cat_test_5");
    tcase_add_test(tc6_1, s21_cat_test_multi_p5);
    suite_add_tcase(s1, tc6_1);

    srunner_run_all(sr, CK_VERBOSE);
    nf = srunner_ntests_failed(sr);
    srunner_free(sr);

    return nf == 0 ? 0 : 1;
}
