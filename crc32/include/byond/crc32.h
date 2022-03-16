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

/**
 * @brief Initial value for CRC-32/BYOND checksums.
 */
extern const uint32_t BYOND_CRC32_DEFAULT;

/**
 * @brief Updates a CRC-32/BYOND checksum.
 *
 * CRC-32/BYOND is a non-reflected checksum with polynomial 0xAF which does
 * not XOR out.
 *
 * @param crc Initial CRC-32/BYOND checksum to update.
 * @param data Input data.
 * @param len Length of the input data.
 * @return The updated CRC-32/BYOND checksum.
 */
uint32_t byond_crc32_update(uint32_t crc, const uint8_t *data, size_t len);

/**
 * @brief Combines two CRC-32/BYOND checksums.
 *
 * @param crc1 Initial CRC-32/BYOND checkum to combine into.
 * @param crc2 A second CRC-32/BYOND checksum to combine into the initial.
 * @param crc2_len Length of input data consumed by crc2.
 * @return The combined CRC-32/BYOND checksum.
 */
uint32_t byond_crc32_combine(uint32_t crc1, uint32_t crc2, size_t crc2_len);

#ifdef __cplusplus
}
#endif  // #ifdef __cplusplus
#endif  // #ifndef BYOND_CRC32_H_
