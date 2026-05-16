#ifndef FASTCOMPRESS_H
#define FASTCOMPRESS_H

#include <jni.h>
#include <cstdint>

namespace fastcompress {

    // CPU Feature Detection
    bool hasAVX2();
    bool hasAVX512F();

    // xxHash64 Core
    uint64_t hashXXH64(const uint8_t* data, size_t length, uint64_t seed);

    // LZ4 Block API (Wrappers)
    int compressLZ4(const uint8_t* src, size_t srcSize, uint8_t* dst, size_t dstCapacity);
    int decompressLZ4(const uint8_t* src, size_t srcSize, uint8_t* dst, size_t dstCapacity);
    size_t getLZ4MaxCompressedSize(size_t inputSize);

    // Zstd API (Wrappers)
    int compressZstd(const uint8_t* src, size_t srcSize, uint8_t* dst, size_t dstCapacity, int level);
    int decompressZstd(const uint8_t* src, size_t srcSize, uint8_t* dst, size_t dstCapacity);

} // namespace fastcompress

#endif // FASTCOMPRESS_H
