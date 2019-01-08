#include "../src/spng.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size)
{
    unsigned char *out = NULL;

    spng_ctx *ctx = spng_ctx_new(0);
    if(ctx == NULL) return 0;

    if(spng_set_png_buffer(ctx, (void*)data, size)) goto err;

    spng_set_image_limits(ctx, 200000, 200000);

    size_t out_size;
    if(spng_decoded_image_size(ctx, SPNG_FMT_RGBA8, &out_size)) goto err;

    out = (unsigned char*)malloc(out_size);
    if(out == NULL) goto err;

    if(spng_decode_image(ctx, out, out_size, SPNG_FMT_RGBA8, 0)) goto err;

err:
    spng_ctx_free(ctx);
    if(out != NULL) free(out);

    return 0;
}
