# CRC-32/BYOND

BYOND's CRC algorithm is a non-bit-reflected 32-bit checksum with polynomial 0xAF which does not XOR out.

## Benchmarks

### 2018 MacBook Pro, 2.2 GHz 6-Core Intel Core i7

```
----------------------------------------------------------------------------------------
Benchmark                              Time             CPU   Iterations UserCounters...
----------------------------------------------------------------------------------------
baseline/1000                       1.99 us         1.99 us       340179 bytes_per_second=480.356M/s
baseline/1000000                    1997 us         1997 us          346 bytes_per_second=477.661M/s
baseline/1000000000              2080410 us      2078082 us            1 bytes_per_second=458.92M/s
byond_crc32_update/1000            0.075 us        0.075 us      8197105 bytes_per_second=12.4825G/s
byond_crc32_update/1000000          50.7 us         50.6 us        14836 bytes_per_second=18.397G/s
byond_crc32_update/1000000000      88869 us        88651 us            6 bytes_per_second=10.5055G/s
````
