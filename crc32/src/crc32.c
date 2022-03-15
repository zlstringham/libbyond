#include <byond/crc32.h>
#include <stddef.h>
#include <stdint.h>

const uint32_t BYOND_CRC32_DEFAULT = 0xffffffff;

uint32_t byond_crc32_update(uint32_t crc, const uint8_t *data, size_t len) {
  for (const uint8_t *end = data + len; data != end; ++data) {
    crc ^= (uint32_t)*data << 24;
    for (int i = 0; i < 8; ++i) {
      if (crc & 0x80000000) {
        crc = (crc << 1) ^ 0xaf;
      } else {
        crc = crc << 1;
      }
    }
  }
  return crc;
}
