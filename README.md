# libbyond

Unofficial C libraries for working with [BYOND](http://byond.com) data.

## Benchmarks

### 2018 MacBook Pro, 2.2 GHz 6-Core Intel Core i7

#### crc32

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

## License

Licensed under either of

 * Apache License, Version 2.0
   ([LICENSE-APACHE](LICENSE-APACHE) or http://www.apache.org/licenses/LICENSE-2.0)
 * MIT license
   ([LICENSE-MIT](LICENSE-MIT) or http://opensource.org/licenses/MIT)

at your option.

## Contribution

Unless you explicitly state otherwise, any contribution intentionally submitted
for inclusion in the work by you, as defined in the Apache-2.0 license, shall be
dual licensed as above, without any additional terms or conditions.
