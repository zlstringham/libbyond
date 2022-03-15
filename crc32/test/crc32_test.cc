#include <byond/crc32.h>
#include <gtest/gtest.h>

#include <cstdint>
#include <string>

const std::string CHECK_STR = "123456789";
const uint32_t CHECK_CRC = 0xa5fd3138;

TEST(ByondCrc32Test, CheckCrc32) {
  EXPECT_EQ(
      byond_crc32_update(BYOND_CRC32_DEFAULT, (const uint8_t *)CHECK_STR.data(),
                         CHECK_STR.size()),
      CHECK_CRC);
}

TEST(ByondCrc32Test, CheckCombine) {
  uint32_t crc1 = byond_crc32_update(BYOND_CRC32_DEFAULT,
                                     (const uint8_t *)CHECK_STR.data(), 3),
           crc2 = byond_crc32_update(BYOND_CRC32_DEFAULT,
                                     (const uint8_t *)CHECK_STR.data() + 3, 3),
           crc3 = byond_crc32_update(BYOND_CRC32_DEFAULT,
                                     (const uint8_t *)CHECK_STR.data() + 6, 3);
  EXPECT_EQ(byond_crc32_combine(byond_crc32_combine(crc1, crc2, 3), crc3, 3),
            CHECK_CRC);
}
