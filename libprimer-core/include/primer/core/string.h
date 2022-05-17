#ifndef _PRIMER_CORE_STRING_H
#define _PRIMER_CORE_STRING_H

#include <stdbool.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct pr_string {
    void *string;
    void *c_string;
} pr_string;

pr_string pr_string_from_c_str(const char *c_str);

pr_string pr_string_from_c_str_sized(const char *c_str, uint64_t len);

bool pr_string_contains(const pr_string string, const pr_string sub);

bool pr_string_starts_with(const pr_string string, const pr_string sub);

bool pr_string_ends_with(const pr_string string, const pr_string sub);

void pr_string_free(pr_string string);

#ifdef __cplusplus
}
#endif

#endif /* _PRIMER_CORE_STRING_H */
