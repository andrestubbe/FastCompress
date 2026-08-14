# FastCompress Design Philosophy

`FastCompress` is engineered around three core high-throughput principles:

1. **Zero Heap Allocation Overhead**: Direct byte buffer native memory access prevents JVM Garbage Collection stalls during large dataset compression.
2. **AVX2 Vectorization**: Leverages 256-bit SIMD registers to compute xxHash64 checksums at 15+ GB/sec.
3. **Ergonomic Overloads**: Combines raw native performance with clean Java helper methods.
