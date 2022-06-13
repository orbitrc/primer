#ifndef _PRIMER_CORE_VECTOR_H
#define _PRIMER_CORE_VECTOR_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct pr_string pr_string;

typedef struct pr_string_vector pr_string_vector;

typedef struct pr_unicode_scalar_vector pr_unicode_scalar_vector;

/*=================*/
/* String Vector   */
/*=================*/

pr_string_vector* pr_string_vector_new();

uint64_t pr_string_vector_length(pr_string_vector *vector);

pr_string* pr_string_vector_get(pr_string_vector *vector, uint64_t index);

void pr_string_vector_free(pr_string_vector *vector);

/*=======================*/
/* Unicode Scalar Vector */
/*=======================*/

pr_unicode_scalar_vector* pr_unicode_scalar_vector_new();

uint64_t pr_unicode_scalar_vector_length(pr_unicode_scalar_vector *vector);

uint32_t pr_unicode_scalar_vector_get(pr_unicode_scalar_vector *vector,
        uint64_t index);

void pr_unicode_scalar_vector_free(pr_unicode_scalar_vector *vector);

#ifdef __cplusplus
}
#endif

#endif /* _PRIMER_CORE_VECTOR_H */
