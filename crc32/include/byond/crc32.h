#ifndef BYOND_CRC32_H_
#define BYOND_CRC32_H_

#ifdef __cplusplus
#include <cstddef>
#include <cstdint>

extern "C" {
#else  // #ifndef __cplusplus
#include <stddef.h>
#include <stdint.h>
#endif  // #ifdef __cplusplus

extern const uint32_t BYOND_CRC32_DEFAULT;

uint32_t byond_crc32_update(uint32_t crc, const uint8_t *data, size_t len);

uint32_t byond_crc32_combine(uint32_t crc1, uint32_t crc2, size_t crc2_len);

#ifdef __cplusplus
}
#endif  // #ifdef __cplusplus
#endif  // #ifndef BYOND_CRC32_H_
