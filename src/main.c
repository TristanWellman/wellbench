#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "generate.h"
#include "argparse/argparse.h"

struct gen_data GDATA;

void help_arg() {

    char *help = "\nWELLANG BENCH CLI HELP:\n\n"
                 "--help        | -h: Need help? Use -h\n"
                 "--vars        | -v: Number of variables to generate\n"
                 "--funcs       | -f: Numver of functions to generate\n"
                 "--ins         | -i: number of instructions to generate\n"
                 "NOTE: You do not have to define vars, funcs, etc.\n"
                 "NOTE: defaults are 6000, 6000, 6000\n"
                 "      6000 instructions for each of the 6000 functions\n";
    printf("%s\n", help);
    exit(0);

}

int main(int argc, char *argv[]) {

    struct ArgparseParser parser = argparse_init("bench", argc, argv);

    argparse_add_option(&parser, "--help", "-h", ARGPARSE_FLAG);
    argparse_add_option(&parser, "--vars", "-v", ARGPARSE_FLAG);
    argparse_add_option(&parser, "--funcs", "-f", ARGPARSE_FLAG);
    argparse_add_option(&parser, "--ins", "-i", ARGPARSE_FLAG);

    if(argc < 2) {
        help_arg();
    }
    if(argparse_option_exists(parser, "--help") != ARGPARSE_NOT_FOUND ||
            argparse_option_exists(parser, "-h") != ARGPARSE_NOT_FOUND) {
        int i;
        for(i = 0; i < 256; i++) {
            if(argv[i] == NULL) {
                break;
            }
            if(!strcmp(argv[i], "--help") || !strcmp(argv[i], "-h")) {
                help_arg();
            }
        }
    }

    GDATA.funcs_tgen = 6000;
    GDATA.ins_tgen = 6000;

    GDATA.muts_tgen = 6000/2;
    GDATA.vars_tgen = 6000/2;

    generate_file(GDATA);

    return 0;

}