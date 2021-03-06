#include <byond/crc32.h>
#include <cpu_features_macros.h>
#include <gtest/gtest.h>

#include <cstdint>
#include <string>
#include <vector>

#ifdef CPU_FEATURES_ARCH_X86
#include <cpuinfo_x86.h>
#endif

const std::string CHECK_STR = "123456789";
const uint32_t CHECK_CRC = 0xa5fd3138;

uint32_t golden(uint32_t crc, const uint8_t *data, size_t len) {
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

TEST(ByondCrc32Test, CheckGolden) {
  const uint8_t *data = (const uint8_t *)CHECK_STR.data();
  EXPECT_EQ(golden(BYOND_CRC32_DEFAULT, data, CHECK_STR.size()), CHECK_CRC);
}

TEST(ByondCrc32Test, CheckCombine) {
  const uint8_t *data = (const uint8_t *)CHECK_STR.data();
  uint32_t crc1 = golden(BYOND_CRC32_DEFAULT, data, 3),
           crc2 = golden(BYOND_CRC32_DEFAULT, data + 3, 3),
           crc3 = golden(BYOND_CRC32_DEFAULT, data + 6, 3);
  EXPECT_EQ(byond_crc32_combine(byond_crc32_combine(crc1, crc2, 3), crc3, 3),
            CHECK_CRC);
}

TEST(ByondCrc32Test, Crc32MatchesGolden) {
  // Test that len < 16B matches. We'll just use the CHECK_STR.
  const uint8_t *data = (const uint8_t *)CHECK_STR.data();
  EXPECT_EQ(byond_crc32_update(BYOND_CRC32_DEFAULT, data, CHECK_STR.size()),
            golden(BYOND_CRC32_DEFAULT, data, CHECK_STR.size()));

  // Test that 16 <= len < 256 matches. This should trigger slice-by-16.
  // If len % 16 != 0 this should check the slice-by-1 impl as well.
  std::vector<uint8_t> data2(54, 0x13);
  EXPECT_EQ(byond_crc32_update(BYOND_CRC32_DEFAULT, data2.data(), data2.size()),
            golden(BYOND_CRC32_DEFAULT, data2.data(), data2.size()));
}

TEST(ByondCrc32Test, PclmulMatchesGolden) {
#ifdef CPU_FEATURES_ARCH_X86
  cpu_features::X86Features features = cpu_features::GetX86Info().features;
  if (features.pclmulqdq && features.sse4_1) {
    // Test the pclmul implementation. Try to maximize the branches taken.
    std::vector<uint8_t> data(256 + 128 * 3 + 16 * 2 + 7, 0x13);
    EXPECT_EQ(byond_crc32_update(BYOND_CRC32_DEFAULT, data.data(), data.size()),
              golden(BYOND_CRC32_DEFAULT, data.data(), data.size()));
  } else {
    GTEST_SKIP();
  }
#else
  GTEST_SKIP();
#endif
}
