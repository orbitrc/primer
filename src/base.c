#include <primer/base.h>

const pr_type pr_int_t_val = {
    .name = "int",
    .size = sizeof(pr_int)
};

const pr_type *pr_int_t = &pr_int_t_val;

const pr_type pr_real_t_val = {
    .name = "real",
    .size = sizeof(pr_real)
};

const pr_type *pr_real_t = &pr_real_t_val;
