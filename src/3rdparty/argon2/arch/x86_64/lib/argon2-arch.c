#include <stdint.h>
#include <string.h>
#include <stdlib.h>

#include "impl-select.h"

#include "argon2-sse2.h"
#include "argon2-ssse3.h"
#include "argon2-xop.h"
#include "argon2-avx2.h"
#include "argon2-avx512f.h"

/* NOTE: there is no portable intrinsic for 64-bit rotate, but any
 * sane compiler should be able to compile this into a ROR instruction: */
#define rotr64(x, n) ((x) >> (n)) | ((x) << (64 - (n)))

#include "argon2-template-64.h"

void fill_segment_default(const argon2_instance_t *instance,
                          argon2_position_t position)
{
    fill_segment_64(instance, position);
}

void argon2_get_impl_list(argon2_impl_list *list)
{
    static const argon2_impl IMPLS[] = {
        { "x86_64",     NULL,                     fill_segment_default },
        { "SSE2",       cpurig_ar2_check_sse2,     cpurig_ar2_fill_segment_sse2 },
        { "SSSE3",      cpurig_ar2_check_ssse3,    cpurig_ar2_fill_segment_ssse3 },
        { "XOP",        cpurig_ar2_check_xop,      cpurig_ar2_fill_segment_xop },
        { "AVX2",       cpurig_ar2_check_avx2,     cpurig_ar2_fill_segment_avx2 },
        { "AVX-512F",   cpurig_ar2_check_avx512f,  cpurig_ar2_fill_segment_avx512f },
    };

    list->count = sizeof(IMPLS) / sizeof(IMPLS[0]);
    list->entries = IMPLS;
}
