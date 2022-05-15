#ifndef _PRIMER_CORE_STRING_H
#define _PRIMER_CORE_STRING_H

#ifdef __cplusplus
extern "C" {
#endif

typedef struct pr_string {
    void *string;
    void *c_string;
} pr_string;

pr_string pr_string_from_c_str(const char *c_str);

void pr_string_free(pr_string string);

#ifdef __cplusplus
}
#endif

#endif /* _PRIMER_CORE_STRING_H */
