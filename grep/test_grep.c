#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <check.h>


int read_file(char** buffer, size_t* size, const char* file);

#define DESTROY(VALUE) if (VALUE) free(VALUE)

#define TEST_GREP(STRING)                                   \
    {                                                       \
        system("./s21_"STRING" >1");                        \
        system(STRING" >2");                                \
        char* buffer1 = NULL;                               \
        char* buffer2 = NULL;                               \
        size_t size1;                                       \
        size_t size2;                                       \
        if (read_file(&buffer1, &size1, "1")) {             \
            printf("%s\n", strerror(errno));                \
        } else {                                            \
            if (read_file(&buffer2, &size2, "2")) {         \
                printf("%s\n", strerror(errno));            \
            } else {                                        \
                ck_assert_int_eq(size1, size2);             \
                ck_assert_mem_eq(buffer1, buffer2, size1);  \
                DESTROY(buffer2);                           \
            }                                               \
            DESTROY(buffer1);                               \
        }                                                   \
    }


START_TEST(s21_grep_test_l) {
    TEST_GREP("grep -l -e if ttt.txt");
    TEST_GREP("grep -l -e for -e if ttt.txt");
    TEST_GREP("grep -li -e for -e if ttt.txt");
    TEST_GREP("grep -l -e return ttt.txt");
    TEST_GREP("grep -lv -e return ttt.txt");
    TEST_GREP("grep -li -e IF ttt.txt");
    TEST_GREP("grep -lin -e IF ttt.txt");
    TEST_GREP("grep -liv -e IF ttt.txt");
    TEST_GREP("grep -l -e argv ttt.txt file.txt");
    TEST_GREP("grep -lv -e argv ttt.txt file.txt");
    TEST_GREP("grep -l -e argv ttt.txt file.txt");
    TEST_GREP("grep -ls -e argv ttt.txt file.txt");
}
END_TEST

START_TEST(s21_grep_test_c) {
    TEST_GREP("grep -c -e if ttt.txt");
    TEST_GREP("grep -c -e for -e if ttt.txt");
    TEST_GREP("grep -ci -e for -e if ttt.txt");
    TEST_GREP("grep -c -e return ttt.txt");
    TEST_GREP("grep -cv -e return ttt.txt");
    TEST_GREP("grep -ci -e IF ttt.txt");
    TEST_GREP("grep -cin -e IF ttt.txt");
    TEST_GREP("grep -civ -e IF ttt.txt");
    TEST_GREP("grep -c -e argv ttt.txt file.txt");
    TEST_GREP("grep -cv -e argv ttt.txt file.txt");
    TEST_GREP("grep -c -e argv ttt.txt file.txt");
    TEST_GREP("grep -ch -e argv ttt.txt file.txt");
    TEST_GREP("grep -cvh -e argv ttt.txt file.txt");
    TEST_GREP("grep -ch -e argv ttt.txt file.txt");
    TEST_GREP("grep -chs -e argv ttt.txt file.txt");
}
END_TEST

START_TEST(s21_grep_test_o) {
    TEST_GREP("grep -o -e if ttt.txt");
    TEST_GREP("grep -o -e for -e if ttt.txt");
    TEST_GREP("grep -oi -e for -e if ttt.txt");
    TEST_GREP("grep -oin -e for -e if ttt.txt");
    TEST_GREP("grep -oin -e for -e if ttt.txt file.txt");
    TEST_GREP("grep -oinv -e for -e if ttt.txt");
    TEST_GREP("grep -o -e return ttt.txt");
    TEST_GREP("grep -ov -e return ttt.txt");
    TEST_GREP("grep -oi -e IF ttt.txt");
    TEST_GREP("grep -oin -e IF ttt.txt");
    TEST_GREP("grep -oiv -e IF ttt.txt");
    TEST_GREP("grep -o -e for ttt.txt file.txt");
    TEST_GREP("grep -o -e argv ttt.txt file.txt");
    TEST_GREP("grep -ov -e argv ttt.txt file.txt");
    TEST_GREP("grep -o -e argv ttt.txt file.txt");
    TEST_GREP("grep -oh -e argv ttt.txt file.txt");
    TEST_GREP("grep -ovh -e argv ttt.txt file.txt");
    TEST_GREP("grep -onh -e argv ttt.txt file.txt");
    TEST_GREP("grep -os -e argv ttt.txt file.txt");
    TEST_GREP("grep -ohs -e argv ttt.txt file.txt");
}
END_TEST


START_TEST(s21_grep_test_f) {
    TEST_GREP("grep -f file.txt ttt.txt");
    TEST_GREP("grep -e while -f file.txt ttt.txt");
    TEST_GREP("grep -e while -eerror -f file.txt ttt.txt");
    TEST_GREP("grep -e while -e end -f file.txt ttt.txt");
    TEST_GREP("grep -i -e while -f file.txt ttt.txt");
    TEST_GREP("grep -in -e while -f file.txt ttt.txt");
    TEST_GREP("grep -in -e while -f file.txt ttt.txt ttt.txt");
    TEST_GREP("grep -inh -e while -f file.txt ttt.txt ttt.txt");
    TEST_GREP("grep -inhv -e while -f file.txt ttt.txt ttt.txt");
    TEST_GREP("grep -v -f file.txt ttt.txt");
    TEST_GREP("grep -vi -f file.txt ttt.txt");
    TEST_GREP("grep -e while -f file.txt ttt.txt");
    TEST_GREP("grep -f file.txt *.*");
}
END_TEST

START_TEST(s21_grep_test_) {
    TEST_GREP("grep if ttt.txt");
    TEST_GREP("grep -i if ttt.txt");
    TEST_GREP("grep -in if ttt.txt");
    TEST_GREP("grep -in if ttt.txt ttt.txt");
    TEST_GREP("grep -inh if ttt.txt ttt.txt");
    TEST_GREP("grep -inv if ttt.txt ttt.txt");
    TEST_GREP("grep -n if file.txt *.*");
    TEST_GREP("grep if -in ttt.txt");
}
END_TEST

int main(void) {
    Suite *s1 = suite_create("grep_tests");
    SRunner *sr = srunner_create(s1);
    int nf;

    TCase *tc1_1 = tcase_create("s21_grep_test_l");
    tcase_add_test(tc1_1, s21_grep_test_l);
    suite_add_tcase(s1, tc1_1);

    TCase *tc2_1 = tcase_create("s21_grep_test_c");
    tcase_add_test(tc2_1, s21_grep_test_c);
    suite_add_tcase(s1, tc2_1);

    TCase *tc3_1 = tcase_create("s21_grep_test_o");
    tcase_add_test(tc3_1, s21_grep_test_o);
    suite_add_tcase(s1, tc3_1);

    TCase *tc4_1 = tcase_create("s21_grep_test_f");
    tcase_add_test(tc4_1, s21_grep_test_f);
    suite_add_tcase(s1, tc4_1);

    TCase *tc5_1 = tcase_create("s21_grep_test_");
    tcase_add_test(tc5_1, s21_grep_test_);
    suite_add_tcase(s1, tc5_1);

    srunner_run_all(sr, CK_VERBOSE);
    nf = srunner_ntests_failed(sr);
    srunner_free(sr);

    return nf == 0 ? 0 : 1;
}

int read_file(char** buffer, size_t* size, const char* file) {
    int error = 0;
    char *source = NULL;

    FILE *fp = fopen(file, "rb");
    if (fp) {
        if (!fseek(fp, 0L, SEEK_END)) {
            long int bufsize = ftell(fp);
            if (bufsize != -1) {
                source = (char*)malloc(bufsize * sizeof(char));
                if (!fseek(fp, 0L, SEEK_SET)) {
                    *size = fread(source, sizeof(char), bufsize, fp);
                    *buffer = source;
                    if (ferror(fp)) {
                        fputs("Error reading file", stderr);
                        error = 1;
                    }
                } else {
                    error = 1;
                }
            } else {
                error = 1;
            }
        } else {
            error = 1;
        }
        fclose(fp);
    } else {
        error = 1;
    }
    return error;
}
