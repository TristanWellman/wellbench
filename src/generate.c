#include <stdio.h>
#include <stdlib.h>
#include "generate.h"

#define VAR_STANDARD_INT "int~ si_"
#define VAR_LONG_INT "long int~ li_"
#define VAR_STRING "string~ s_"
#define MUT_MUT "mut~ mm_"

#define GENERIC_INS "move~"

char *var_hold = "~include <std.well>\n"
                 "~var:main { \n";
char *func_holf = "~func:gen_";

int generate_file(struct gen_data GEN_DATA) {
    FILE *GENERATED_FILE = fopen("gen.well", "a");
    char line[256];


    fprintf(GENERATED_FILE, "%s", var_hold);
    int i,j,k,l;
    int num_of_ints = GEN_DATA.vars_tgen/3;
    int num_of_lints = num_of_ints;
    int num_of_strings = num_of_ints;

    int num_of_muts = GEN_DATA.muts_tgen;

    int num_of_funcs = GEN_DATA.funcs_tgen;
    int num_of_ins = GEN_DATA.ins_tgen;
    for(i = 0; i < num_of_ints && num_of_lints && num_of_strings;i++) {
        char buf[0x100];
        char buf_[0x100];
        char buf__[0x100];

        snprintf(buf, sizeof(buf),
                 "%s_%d = 1", VAR_STANDARD_INT, i);
        snprintf(buf_, sizeof(buf_),
                 "%s_%d = 1", VAR_LONG_INT, i);
        snprintf(buf__, sizeof(buf__),
                 "%s_%d = 1", VAR_STRING, i);

        fprintf(GENERATED_FILE,
                "\t%s\n\t%s\n\t%s\n",
                buf,buf_,buf__);
    }
    for(j = 0; j < num_of_muts; j++) {
        char buf[0x100];
        snprintf(buf, sizeof(buf),
                 "%s_%d = resq 1", MUT_MUT, j);
        fprintf(GENERATED_FILE, "\t%s\n", buf);
    }
    fprintf(GENERATED_FILE, "}\n");

    for(k = 0; k < num_of_funcs; k++) {

        char buf[0x100];
        snprintf(buf, sizeof(buf),
                 "%s_%d {", func_holf, k);
        fprintf(GENERATED_FILE, "%s\n", buf);
        for(l = 0; l < num_of_ins; l++) {
            char buf[0x100];
            if(l < num_of_ints) {
                snprintf(buf, sizeof(buf),
                         "%s si__%d, rax", GENERIC_INS,  l);
            } else if(l < 2000 && l > num_of_ints) {
                snprintf(buf, sizeof(buf),
                         "%s li__%d, rax", GENERIC_INS,  l);
            } else if(l < 3000 && l > 2000) {
                snprintf(buf, sizeof(buf),
                         "%s s___%d, rax", GENERIC_INS,  l);
            } else if(l >= 3000) {
                snprintf(buf, sizeof(buf),
                         "%s mm__%d, rax", GENERIC_INS,  l);
            }
            fprintf(GENERATED_FILE, "\t%s\n", buf);
        }
        fprintf(GENERATED_FILE, "\n}\n");
    }


    fprintf(GENERATED_FILE,
            "~func:main {\treturn~ 0\n}");
    fclose(GENERATED_FILE);

    system("wesm gen.well -a");
    return 0;
}
