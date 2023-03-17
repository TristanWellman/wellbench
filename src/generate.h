#ifndef BENCH_GENERATE_H
#define BENCH_GENERATE_H

struct gen_data {

    int vars_tgen;
    int muts_tgen;
    int funcs_tgen;
    int ins_tgen;

};

int generate_file(struct gen_data GEN_DATA);

#endif
