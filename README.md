# libbyond

Unofficial C libraries for working with [BYOND](http://byond.com) data.

BYOND itself uses a "libbyond" shared library; this is not that. This is to be a compilation of separate libraries which make up individual aspects of the BYOND ecosystem.

## Libraries
- [x] crc32
   - [x] SIMD implementation for x86 platforms 
   - [ ] SIMD implementation for ARM/AARCH64 platforms
- [ ] dmitext - Parse and generate the text metadata of BYOND's PNG-based .dmi format
- [ ] dmi4 - Decode BYOND's legacy DMI "4" format
- [ ] rsc - Decode/Encode BYOND's resource format
- [ ] dmm - Parse and write BYOND's map format
- [ ] dmf - Parse and write BYOND's interface format
- [ ] regex - BYOND's regex algorithm
- [ ] ???

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
