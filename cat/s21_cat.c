#define _GNU_SOURCE

#include <getopt.h>
#include <stdio.h>

struct s21_cat {
    int b;
    int e;
    int n;
    int s;
    int t;
    int v;
};

int output(char* argv, struct s21_cat opts);

int main(int argc, char* argv[]) {
    if (argc > 1) {
        const char* opt_string = "benstvET";
        const struct option long_opts[] = {
            {"--number-nonblank", no_argument, NULL, 'b'},
            {"--number", no_argument, NULL, 'n'},
            {"--squeeze-blank", no_argument, NULL, 's'},
        };

        struct s21_cat opts = {0, 0, 0, 0, 0, 0};
        int long_index = -1;
        int error = 0;

        for (int opt; (opt = getopt_long(argc, argv, opt_string, long_opts,
                                         &long_index)) != -1;) {
            switch (opt) {
                case 'b':
                    opts.b = 1;
                    break;
                case 'E':
                case 'e':
                    opts.e = 1;
                    opts.v = 1;
                    break;
                case 'n':
                    opts.n = 1;
                    break;
                case 's':
                    opts.s = 1;
                    break;
                case 'T':
                case 't':
                    opts.t = 1;
                    opts.v = 1;
                    break;
                case 'v':
                    opts.v = 1;
                    break;
                case '?':
                    printf("error");
                    error = 1;
                    break;
                default:
                    break;
            }
        }
        if (!error) {
            for (int index = 1; index != argc; index++) {
                output(argv[index], opts);
            }
        }
    }
}

int output(char* cat_file, struct s21_cat opts) {
    if (*cat_file != '-') {
        FILE* fp;
        fp = fopen(cat_file, "rt");

        char prev = '\n';
        size_t num = 1;
        int new_line;
        int empty_string;
        int temp = 0;

        while (!feof(fp) && !ferror(fp)) {
            int current_char = fgetc(fp);
            if (current_char != -1) {
                int flag_v = 0;
                if (opts.s) {
                    if (current_char == '\n') temp++;
                    if (current_char != '\n') temp = 0;
                }

                if (current_char == '\n' && prev == '\n')
                    empty_string = 1;
                else
                    empty_string = 0;

                if (prev == '\n' || current_char == '\0')
                    new_line = 1;
                else
                    new_line = 0;

                if (opts.n && !opts.b && new_line && temp < 3) {
                    printf("%6zu\t", num);
                    new_line = 0;
                }

                if (opts.b && new_line && temp < 3) {
                    if (!empty_string) printf("%6zu\t", num);
                    if (empty_string) num--;
                    empty_string = 0;
                }

                if (current_char == '\n') {
                    if (!opts.b && temp < 3)
                        num++;
                    else if (opts.b && !empty_string)
                        num++;
                }
                if (opts.v && temp < 3) {
                    if (opts.e && current_char == '\n') printf("$");
                    if (current_char < 9 || (current_char > 10 && current_char < 32)) {
                        printf("^%c", current_char + 64);
                        flag_v = 1;
                    } else if (current_char == '\t' && opts.t) {
                        printf("^I");
                    } else if (current_char == 127) {
                        printf("^%c", current_char - 64);
                        flag_v = 1;
                    } else if (current_char > 127 && current_char < 160) {
                        printf("M-^%c", current_char - 64);
                        flag_v = 1;
                    }
                }
                if (!feof(fp) && !opts.s && temp < 3 && !flag_v && !(opts.t && current_char == '\t'))
                    putchar(current_char);
                if (opts.s && temp < 3) {
                    if (!feof(fp) && !flag_v && !(opts.t && current_char == '\t'))
                        putchar(current_char);
                }
                prev = current_char;
            }
        }
    }
    return 0;
}
