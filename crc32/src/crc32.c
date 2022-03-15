#include <byond/crc32.h>
#include <stddef.h>
#include <stdint.h>

#include "lut_impl.h"

const uint32_t BYOND_CRC32_DEFAULT = 0xffffffff;

uint32_t byond_crc32_update(uint32_t crc, const uint8_t *data, size_t len) {
  return crc32_slice_by_16(crc, data, len);
}
