#include "parser_internal.h"

static HParseResult *parse_aligned(void *pn, HParseState *state) {
    size_t n = *(size_t *)pn;
    size_t index = state->input_stream.index;
    size_t offset = state->input_stream.bit_offset;

    size_t pos = (index % n) * (8 % n) + (offset % n);

    if(pos%n != 0) {
        // not aligned, fail
        return NULL;
    } else {
        return make_result(state->arena, NULL);
    }
}

static const HParserVtable aligned_vt = {
    .parse = parse_aligned,
    .isValidRegular = h_false,
    .isValidCF = h_false,
    .compile_to_rvm = h_not_regular,
    .higher = true,
};

HParser *h_aligned(size_t n)
{
    return h_aligned__m(&system_allocator, n);
}

HParser *h_aligned__m(HAllocator *mm__, size_t n)
{
    size_t *pn = h_new(size_t, 1);
    *pn = n;

    return h_new_parser(mm__, &aligned_vt, pn);
}
