#ifndef _PRIMER_CORE_RANGE_H
#define _PRIMER_CORE_RANGE_H

#include <stdbool.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct pr_range {
    int64_t start;
    int64_t end;
    bool exclusive;
} pr_range;

pr_range pr_range_new(int64_t start, int64_t end, bool exclusive);


void pr_range_free(pr_range range);


int64_t pr_range_start(const pr_range range);

int64_t pr_range_end(const pr_range range);

bool pr_range_exclusive(const pr_range range);

bool pr_range_contains(const pr_range range, int64_t value);

int64_t pr_range_random(const pr_range range);

uint64_t pr_range_random_u(const pr_range range);

#ifdef __cplusplus
}
#endif

#endif // _PRIMER_CORE_RANGE_H