#include <byond/crc32.h>
#include <stddef.h>
#include <stdint.h>

const uint32_t COMBINE_TABLE[32] = {
    0x00000100, 0x00010000, 0x000000af, 0x00004455, 0x10101111, 0xae01ae01,
    0x1bd81099, 0x87f2f581, 0x9dd170d4, 0x5bbedfd6, 0x27afa5be, 0xf0db1b29,
    0x2264a683, 0xfaa007ab, 0x0a402c54, 0x2d26e110, 0xc99cb412, 0x5e545a7b,
    0x6dc24493, 0x7dae76c1, 0xd7a20af5, 0x978e3ee2, 0x629ca6e1, 0x0a831f49,
    0x2802d252, 0xc6c412e6, 0x39697bab, 0x2d222274, 0x9999aaf2, 0x00000002,
    0x00000004, 0x00000010,
};

uint32_t multmodp(uint32_t a, uint32_t b);
uint32_t x8nmodp(size_t n);

uint32_t byond_crc32_combine(uint32_t crc1, uint32_t crc2, size_t crc2_len) {
  return multmodp(x8nmodp(crc2_len), ~crc1) ^ crc2;
}

uint32_t multmodp(uint32_t a, uint32_t b) {
  uint32_t prod = 0;
  while (1) {
    if (a & 1) {
      prod ^= b;
      if (a == 1) {
        break;
      }
    }
    a >>= 1;
    if (b & 0x80000000) {
      b = (b << 1) ^ 0xaf;
    } else {
      b <<= 1;
    }
  }
  return prod;
}

uint32_t x8nmodp(size_t n) {
  uint32_t xp = 1;
  int k = 0;
  while (n) {
    if (n & 1) {
      xp = multmodp(COMBINE_TABLE[k], xp);
    }
    n >>= 1;
    k = (k + 1) & 0x1f;
  }
  return xp;
}
