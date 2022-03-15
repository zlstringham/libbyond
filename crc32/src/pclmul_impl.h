#ifndef BYOND_CRC32_PCLMUL_IMPL_H_
#define BYOND_CRC32_PCLMUL_IMPL_H_

#include <immintrin.h>
#include <stddef.h>
#include <stdint.h>

#include "lut_impl.h"

const uint64_t RK01 = 0x00295f2300000000;
const uint64_t RK02 = 0xfafa517900000000;
const uint64_t RK03 = 0x5cd86bb500000000;
const uint64_t RK04 = 0xaf6f37a300000000;
const uint64_t RK05 = 0x00295f2300000000;
const uint64_t RK06 = 0x0000445500000000;
const uint64_t RK07 = 0x00000001000000af;
const uint64_t RK08 = 0x00000001000000af;
const uint64_t RK09 = 0x9bd57b5d00000000;
const uint64_t RK10 = 0xb7a4d76400000000;
const uint64_t RK11 = 0x1ae0004200000000;
const uint64_t RK12 = 0xe7720be600000000;
const uint64_t RK13 = 0x9c7fc8fe00000000;
const uint64_t RK14 = 0x3885faf800000000;
const uint64_t RK15 = 0xb477ad7100000000;
const uint64_t RK16 = 0x0ac2ae3d00000000;
const uint64_t RK17 = 0x5eae9dbe00000000;
const uint64_t RK18 = 0x784a483800000000;
const uint64_t RK19 = 0x7d21bf2000000000;
const uint64_t RK20 = 0xfaebd3d300000000;

inline __m128i reduce128(const __m128i a, const __m128i b, const __m128i keys) {
  __m128i t1 = _mm_clmulepi64_si128(a, keys, 0x00);
  __m128i t2 = _mm_clmulepi64_si128(a, keys, 0x11);
  return _mm_xor_si128(_mm_xor_si128(b, t1), t2);
}

inline __m128i get(const uint8_t **data, size_t *len, const __m128i smask) {
  __m128i r = _mm_shuffle_epi8(_mm_loadu_si128((const __m128i *)*data), smask);
  *data += 16;
  *len -= 16;
  return r;
}

uint32_t crc32_pclmul(uint32_t crc, const uint8_t *data, size_t len) {
  if (len < 256) {
    // This could be handled in intrinsics, but the logic is messy and this
    // seems fine for now.
    return crc32_slice_by_16(crc, data, len);
  }

  // Shuffle mask for byte-swapping 16 bytes.
  const __m128i smask = _mm_set_epi8(0x0, 0x1, 0x2, 0x3, 0x4, 0x5, 0x6, 0x7,
                                     0x8, 0x9, 0xa, 0xb, 0xc, 0xd, 0xe, 0xf);

  // Load initial 128B of data.
  __m128i x7 = get(&data, &len, smask);
  __m128i x6 = get(&data, &len, smask);
  __m128i x5 = get(&data, &len, smask);
  __m128i x4 = get(&data, &len, smask);
  __m128i x3 = get(&data, &len, smask);
  __m128i x2 = get(&data, &len, smask);
  __m128i x1 = get(&data, &len, smask);
  __m128i x0 = get(&data, &len, smask);

  // XOR in the initial CRC.
  const __m128i crc_m128i = _mm_set_epi32(crc, 0x0000, 0x0000, 0x0000);
  x7 = _mm_xor_si128(x7, crc_m128i);

  const __m128i k3k4 = _mm_set_epi64x(RK04, RK03);
  while (len >= 128) {
    x7 = reduce128(x7, get(&data, &len, smask), k3k4);
    x6 = reduce128(x6, get(&data, &len, smask), k3k4);
    x5 = reduce128(x5, get(&data, &len, smask), k3k4);
    x4 = reduce128(x4, get(&data, &len, smask), k3k4);
    x3 = reduce128(x3, get(&data, &len, smask), k3k4);
    x2 = reduce128(x2, get(&data, &len, smask), k3k4);
    x1 = reduce128(x1, get(&data, &len, smask), k3k4);
    x0 = reduce128(x0, get(&data, &len, smask), k3k4);
  }

  const __m128i k1k2 = _mm_set_epi64x(RK02, RK01);
  __m128i x = reduce128(x7, x0, _mm_set_epi64x(RK10, RK09));
  x = reduce128(x6, x, _mm_set_epi64x(RK12, RK11));
  x = reduce128(x5, x, _mm_set_epi64x(RK14, RK13));
  x = reduce128(x4, x, _mm_set_epi64x(RK16, RK15));
  x = reduce128(x3, x, _mm_set_epi64x(RK18, RK17));
  x = reduce128(x2, x, _mm_set_epi64x(RK20, RK19));
  x = reduce128(x1, x, k1k2);

  while (len >= 16) {
    x = reduce128(x, get(&data, &len, smask), k1k2);
  }

  // Reduce 128b to 64b.
  const __m128i k5k6 = _mm_set_epi64x(RK06, RK05);
  x = _mm_xor_si128(_mm_clmulepi64_si128(x, k5k6, 0x01), _mm_slli_si128(x, 8));
  x = _mm_xor_si128(_mm_clmulepi64_si128(_mm_srli_si128(x, 12), k5k6, 0x10),
                    _mm_and_si128(x, _mm_set_epi32(0, ~0, ~0, ~0)));

  // Barrett reduction, 64b to 32b.
  const __m128i k7k8 = _mm_set_epi64x(RK08, RK07);
  __m128i t1 = _mm_slli_si128(_mm_clmulepi64_si128(x, k7k8, 0x01), 4);
  __m128i t2 = _mm_slli_si128(_mm_clmulepi64_si128(t1, k7k8, 0x11), 4);
  crc = _mm_extract_epi32(_mm_xor_si128(x, t2), 1);

  if (len) {
    // We could use intrinsics for the remaining data, but this seems fine for
    // now. Less than 16B remaining, so slice-by-1 instead of slice-by-16.
    return crc32_slice_by_1(crc, data, len);
  } else {
    return crc;
  }
}

#endif  // #ifndef BYOND_CRC32_PCLMUL_IMPL_H_
