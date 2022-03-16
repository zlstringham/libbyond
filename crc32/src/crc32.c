#include <byond/crc32.h>
#include <cpu_features_macros.h>
#include <stddef.h>
#include <stdint.h>

#include "lut_impl.h"

#ifdef CPU_FEATURES_ARCH_X86
#include <cpuinfo_x86.h>

#include "pclmul_impl.h"
#endif

const uint32_t BYOND_CRC32_DEFAULT = 0xffffffff;

uint32_t byond_crc32_update(uint32_t crc, const uint8_t *data, size_t len) {
#ifdef CPU_FEATURES_ARCH_X86
  // Detect availability of SIMD instruction set.
  static int use_pclmul = 0;
  static int use_pclmul_isset = 0;
  if (!use_pclmul_isset) {
    X86Features features = GetX86Info().features;
    use_pclmul = features.pclmulqdq && features.sse4_1;
    use_pclmul_isset = 1;
  }
  if (use_pclmul) {
    return crc32_pclmul(crc, data, len);
  } else {
    return crc32_slice_by_16(crc, data, len);
  }
#else
  return crc32_slice_by_16(crc, data, len);
#endif
}
