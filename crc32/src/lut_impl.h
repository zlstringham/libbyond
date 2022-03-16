#ifndef BYOND_CRC32_LUT_IMPL_H_
#define BYOND_CRC32_LUT_IMPL_H_

#include <stddef.h>
#include <stdint.h>

#include "tables.h"

uint32_t bswap_32(uint32_t x) {
  return (x >> 0x18) | ((x << 0x08) & 0x00ff0000) | ((x >> 0x08) & 0x0000ff00) |
         (x << 0x18);
}

uint32_t crc32_slice_by_1(uint32_t crc, const uint8_t *data, size_t len) {
  for (const uint8_t *end = data + len; data != end; ++data) {
    crc = (crc << 8) ^ CRC32_BYTE_TABLE[(crc >> 24) ^ *data];
  }
  return crc;
}

uint32_t crc32_slice_by_16(uint32_t crc, const uint8_t *data, size_t len) {
  if (len >= 16) {
    crc = bswap_32(crc);
    do {
      crc =
          CRC32_WORD_TABLE[0xf][data[0x0] ^ (crc & 0xff)] ^
          CRC32_WORD_TABLE[0xe][data[0x1] ^ ((crc >> 0x08) & 0xff)] ^
          CRC32_WORD_TABLE[0xd][data[0x2] ^ ((crc >> 0x10) & 0xff)] ^
          CRC32_WORD_TABLE[0xc][data[0x3] ^ (crc >> 0x18)] ^
          CRC32_WORD_TABLE[0xb][data[0x4]] ^ CRC32_WORD_TABLE[0xa][data[0x5]] ^
          CRC32_WORD_TABLE[0x9][data[0x6]] ^ CRC32_WORD_TABLE[0x8][data[0x7]] ^
          CRC32_WORD_TABLE[0x7][data[0x8]] ^ CRC32_WORD_TABLE[0x6][data[0x9]] ^
          CRC32_WORD_TABLE[0x5][data[0xa]] ^ CRC32_WORD_TABLE[0x4][data[0xb]] ^
          CRC32_WORD_TABLE[0x3][data[0xc]] ^ CRC32_WORD_TABLE[0x2][data[0xd]] ^
          CRC32_WORD_TABLE[0x1][data[0xe]] ^ CRC32_WORD_TABLE[0x0][data[0xf]];
      data += 16;
      len -= 16;
    } while (len >= 16);
    crc = bswap_32(crc);
  }
  return crc32_slice_by_1(crc, data, len);
}

#endif  // #ifndef BYOND_CRC32_LUT_IMPL_H_
