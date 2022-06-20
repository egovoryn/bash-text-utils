#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define MAX_LEN 1024

struct opts {
    int e;
    int i;
    int v;
    int c;
    int l;
    int n;
    int h;
    int s;
    int f;
    int o;
    char pattern[MAX_LEN];
    char filename[MAX_LEN];
};

int output(const char* file, struct opts grep_opts);
int regular(const char* str, const char* pattern, int opt_i);
int regular_coin(const char* str, const char* file, const size_t num_str, struct opts grep_opt);
void print_str(const char* str, const char* file, const size_t num_str, struct opts grep_opt);
int create_pattern(struct opts* grep_opts);

int main(int argc, char* argv[]) {
    struct opts grep_opts = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, "", ""};
    int error = 0;
    // optind - Индекс текущего параметра
    // optarg - значение параметра (указатель просто указывает на элемент массива argv[])
    if (argc > 1 && *argv[1] != '-') {
        snprintf(grep_opts.pattern, MAX_LEN, "%s", argv[1]);
        getopt(argc, argv, "e:ivclnhsf:o");
        optind++;
    }
    for (int opt; (opt = getopt(argc, argv, "e:ivclnhsf:o")) != -1;) {
        switch (opt) {
            case 'e':
                grep_opts.e = 1;
                if (!strlen(grep_opts.pattern))
                    snprintf(grep_opts.pattern, MAX_LEN, "%s", optarg);
                else
                    snprintf(grep_opts.pattern + strlen(grep_opts.pattern),
                             MAX_LEN - strlen(grep_opts.pattern), "|%s", optarg);
                // смещаем указатель в строке pattern на длину уже записанной части
                // уменьшаем возможный размер массива pattern на длину уже записанной части
                break;
            case 'i':
                grep_opts.i = 1;
                break;
            case 'v':
                grep_opts.v = 1;
                break;
            case 'c':
                grep_opts.c = 1;
                break;
            case 'l':
                grep_opts.l = 1;
                break;
            case 'n':
                grep_opts.n = 1;
                break;
            case 'h':
                grep_opts.h = 1;
                break;
            case 's':
                grep_opts.s = 1;
                break;
            case 'f':
                grep_opts.f = 1;
                snprintf(grep_opts.filename, MAX_LEN, "%s", optarg);
                break;
            case 'o':
                grep_opts.o = 1;
                break;
            case '?':
                error = 2;
                break;
        }
    }
    if (!error && argc > 1) {
        int index = optind;
        if (!grep_opts.e && !grep_opts.f && index < argc && !strlen(grep_opts.pattern)) {
            snprintf(grep_opts.pattern, MAX_LEN, "%s", argv[index]);
            index++;
        } else {
            if (grep_opts.f) {
                if (create_pattern(&grep_opts)) {
                    printf("error\n");
                    error = 2;
                }
            }
        }
        if ((argc - index) == 1) grep_opts.h = 1;  // если файл один - название не выводится
        if (!error) {
            for (; index < argc; index++) {
                if (output(argv[index], grep_opts)) error = 2;
            }
        }
    } else {
        printf("error\n");
        error = 2;
    }
    // error = 2 - не может получить аргумент из командной строки
    return error;
}

int output(const char* file, struct opts grep_opts) {
    FILE* fp;
    fp = fopen(file, "rt");

    int error = 0;
    if (fp) {
        char* str = NULL;             // буфер для считывания строк из файла
        size_t len_str = 0;           // размер считываемой строки (malloc/realloc)
        ssize_t num_read = 0;         // количество символов в строке, включая \n
        size_t num_str = 0;           // номер строки
        int while_exit = 1;           // флаг для выхода из цикла
        size_t count_sut_line = 0;    // количество совпадающих срок
        size_t count_unsut_line = 0;  // количество НЕсовпадающих срок

        while ((num_read = getline(&str, &len_str, fp)) != -1 && str && while_exit) {
            if (feof(fp) && num_read > 0 && str[num_read - 1] != '\n') {
                char* new_str = (char*)realloc(str, num_read + 2);
                if (!new_str) {
                    printf("error\n");
                    error = 1;
                    break;
                } else {
                    str = new_str;
                    snprintf(str + num_read, num_read + 2, "%c", '\n');
                    // если в файле одна строка без переноса - добавить \n в конец вывода
                }
            }
            num_str++;
            if (grep_opts.l) {
                if (!grep_opts.v) {
                    if (!regular(str, grep_opts.pattern, grep_opts.i)) {
                        printf("%s\n", file);
                        while_exit = 0;
                    }
                } else {
                    if (grep_opts.v && grep_opts.c && grep_opts.o)
                        printf("%d\n", 1);
                    if (grep_opts.v && grep_opts.l) {
                        if (regular(str, grep_opts.pattern, grep_opts.i)) printf("%s\n", file);
                    } else {
                        printf("%s\n", file);
                    }
                    while_exit = 0;
                }
            } else if (grep_opts.c) {
                if (!regular(str, grep_opts.pattern, grep_opts.i))
                    count_sut_line++;
                else
                    count_unsut_line++;
            } else if (grep_opts.o) {
                if (!grep_opts.v)
                    regular_coin(str, file, num_str, grep_opts);
            }
            if (grep_opts.v && !grep_opts.l && !grep_opts.c) {
                if (regular(str, grep_opts.pattern, grep_opts.i))
                    print_str(str, file, num_str, grep_opts);
            } else if (!grep_opts.v && !grep_opts.l && !grep_opts.c && !grep_opts.o) {
                if (!regular(str, grep_opts.pattern, grep_opts.i))
                    print_str(str, file, num_str, grep_opts);
            }
        }
        if (str) free(str);  // освобождаем строку str из getline
        if (!error) {
            if (grep_opts.c) {
                if (!grep_opts.h) printf("%s:", file);
                if (!grep_opts.v) {
                    printf("%zu\n", count_sut_line);
                } else if (grep_opts.v && grep_opts.l && grep_opts.o) {
                } else {
                    printf("%zu\n", count_unsut_line);
                }
            }
        }
        fclose(fp);
    } else {
        if (!grep_opts.c) {
            printf("error\n");
            error = 1;
        }
    }
    return error;
}

int regular(const char* str, const char* pattern, int opt_i) {
    int result = 0;     // 0 - found, 1 - not found, -1 - wrong pattern
    regex_t compilied;  // структурный тип данных для хранения скомпилированного регулярного выражения

    int res_val = 0;  // логическое выражение для результата regcomp
    if (opt_i)
        res_val = regcomp(&compilied, pattern, REG_EXTENDED | REG_ICASE);
    else
        res_val = regcomp(&compilied, pattern, REG_EXTENDED);
    // компилирует указанный шаблон регулярного выражения в определенный формат данных

    if (res_val) {  // успешное выполнение regcomp возвращает 0
        printf("error\n");
        result = -1;
    } else {
        regmatch_t match;
        result = regexec(&compilied, str, 1, &match, 0);
        // регулярное выражение compilied сопоставляем с целевой текстовой строкой str
        regfree(&compilied);
        // очистить содержимое структуры regex_t
    }
    return result;
}

void print_str(const char* str, const char* file, const size_t num_str, struct opts grep_opt) {
    if (!grep_opt.h) printf("%s:", file);
    if (grep_opt.n) printf("%zu:", num_str);
    printf("%s", str);
}

int regular_coin(const char* str, const char* file, const size_t num_str, struct opts grep_opt) {
    int result = 1;              // 0 - found, 1 - not found, -1 - wrong pattern
    regex_t compilied;           // структурный тип данных для скомпилированного регулярного выражения
    char* str_ptr = (char*)str;  // указатель на str (кастованная const char в char)

    int res_val = 0;  // логическое выражение для результата regcomp
    if (grep_opt.i)
        res_val = regcomp(&compilied, grep_opt.pattern, REG_EXTENDED | REG_ICASE);
    else
        res_val = regcomp(&compilied, grep_opt.pattern, REG_EXTENDED);

    if (res_val) {  // regcomp return 0 if success
        printf("error\n");
        result = -1;
    } else {
        regmatch_t match;
        // typedef struct {
        //    regoff_t rm_so;
        //    regoff_t rm_eo;
        // } regmatch_t;
        // Элемент rm_so сохраняет начальную позицию соответствующей текстовой строки
        // в целевой строке, а rm_eo сохраняет конечную позицию.

        if (!grep_opt.h && !regular(str, grep_opt.pattern, grep_opt.i)) printf("%s:", file);
        if (grep_opt.n && !regular(str, grep_opt.pattern, grep_opt.i)) printf("%zu:", num_str);

        while (!regexec(&compilied, str_ptr, 1, &match, 0)) {
            // regexec(искомое регулярное выражение | строка из файла для поиска |
            // 1 - только одно совпадение | структура сохраняющая начало и конец совпадения |
            // 0 - возвращает при успехе)
            result = 0;
            printf("%.*s\n", (int)(match.rm_eo - match.rm_so), str_ptr + match.rm_so);
            str_ptr += match.rm_eo;
        }
        regfree(&compilied);
    }
    return result;
}

int create_pattern(struct opts* grep_opts) {
    int error = 0;
    FILE* fp;

    fp = fopen(grep_opts->filename, "rt");
    if (fp) {
        char* str = NULL;
        size_t len_str = 0;
        ssize_t num_read = 0;
        if (!grep_opts->e) {
            if ((num_read = getline(&str, &len_str, fp)) != -1 && str) {
                if (num_read > 1 && str[num_read - 1] == '\n') {
                    // заменяет перенос строки на строкой разделитель
                    // для считывания нескольких паттернов из файла
                    str[num_read - 1] = '\0';
                }
                snprintf(grep_opts->pattern, MAX_LEN, "%s", str);
            }
        }
        while ((num_read = getline(&str, &len_str, fp)) != -1 && str) {
            if (num_read > 1 && str[num_read - 1] == '\n') {
                str[num_read - 1] = '\0';
            }
            snprintf(grep_opts->pattern + strlen(grep_opts->pattern),
                     MAX_LEN - strlen(grep_opts->pattern), "|%s", str);
            // смещаем указатель в строке pattern на длину уже записанной части
            // уменьшаем возможный размер массива pattern на длину уже записанной части
        }
        if (str) free(str);
        fclose(fp);
    } else {
        error = 1;
    }
    return error;
}
