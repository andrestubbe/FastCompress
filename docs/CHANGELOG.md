# FastCompress Changelog

## [0.1.1] - 2026-08-14
- Integrated native `FastSIMD` (v0.1.3) AVX2 vector compression primitives.
- Added convenient helper overloads `compressLZ4(byte[])` and `decompressLZ4(byte[], int)`.
- Added official JMH benchmark suite measuring 8.79M LZ4 ops/sec.
- Placed Quick Start at top above Table of Contents in README.md.
- Added `Key Features`, `Real-World Use Cases`, and `Performance Benchmarks` sections.
- Updated full 5-module installation stack (`FastCompress`, `FastSIMD`, `FastMemory`, `FastPointer`, `FastBytes`).

## [0.1.0] - 2026-05-18
- Initial release of FastCompress with LZ4 and xxHash64 C++ bindings.
