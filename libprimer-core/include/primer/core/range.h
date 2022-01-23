#ifndef _PRIMER_CORE_RANGE_H
#define _PRIMER_CORE_RANGE_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct pr_range {
    void *range;
} pr_range;

pr_range* pr_range_new_i8(int8_t start, int8_t end);

pr_range* pr_range_new_u8(uint8_t start, uint8_t end);

pr_range* pr_range_new_i16(int16_t start, int16_t end);

pr_range* pr_range_new_u16(uint16_t start, uint16_t end);

pr_range* pr_range_new_i32(int32_t start, int32_t end);

pr_range* pr_range_new_u32(uint32_t start, uint32_t end);

pr_range* pr_range_new_i64(int64_t start, int64_t end);

pr_range* pr_range_new_u64(uint64_t start, uint64_t end);

void pr_range_free(pr_range *range);

#ifdef __cplusplus
}
#endif

#endif // _PRIMER_CORE_RANGE_H