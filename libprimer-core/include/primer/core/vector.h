#ifndef _PRIMER_CORE_VECTOR_H
#define _PRIMER_CORE_VECTOR_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct pr_string pr_string;

typedef struct pr_string_vector pr_string_vector;


pr_string_vector* pr_string_vector_new();

void pr_string_vector_free(pr_string_vector *vector);

#ifdef __cplusplus
}
#endif

#endif /* _PRIMER_CORE_VECTOR_H */
