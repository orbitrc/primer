#ifndef _PRIMER_CORE_JSON_H
#define _PRIMER_CORE_JSON_H

#include <stdbool.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef enum pr_json_type {
    PR_JSON_TYPE_NULL = 0,
    PR_JSON_TYPE_BOOL = 1,
    PR_JSON_TYPE_INT = 2,
    PR_JSON_TYPE_DOUBLE = 3,
    PR_JSON_TYPE_STRING = 4,
    PR_JSON_TYPE_ARRAY = 5,
    PR_JSON_TYPE_OBJECT = 6,
} pr_json_type;

typedef struct pr_json_value {
    void *value;
    pr_json_type json_type;
} pr_json_value;

pr_json_value pr_json_null_new();

pr_json_value pr_json_bool_new(bool value);

pr_json_value pr_json_int_new(int64_t value);

pr_json_value pr_json_double_new(double value);

pr_json_value pr_json_string_new(const char *value);

#ifdef __cplusplus
}
#endif

#endif /* _PRIMER_CORE_JSON_H */
