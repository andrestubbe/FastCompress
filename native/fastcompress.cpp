#include "fastcompress.h"
#include <immintrin.h>
#include <cstring>

#ifdef _MSC_VER
#include <intrin.h>
#endif

namespace fastcompress {

// --- CPU Feature Detection ---
static bool g_avx2 = false;
static bool g_avx512f = false;
static bool g_initialized = false;

static void initCpuFeatures() {
    if (g_initialized) return;
    int cpuInfo[4] = {0};
#ifdef _MSC_VER
    __cpuid(cpuInfo, 1);
#else
    __cpuid(1, cpuInfo[0], cpuInfo[1], cpuInfo[2], cpuInfo[3]);
#endif
    bool hasAVX = (cpuInfo[2] & (1 << 28)) != 0;
    if (hasAVX) {
#ifdef _MSC_VER
        __cpuidex(cpuInfo, 7, 0);
#else
        __cpuid_count(7, 0, cpuInfo[0], cpuInfo[1], cpuInfo[2], cpuInfo[3]);
#endif
        g_avx2 = (cpuInfo[1] & (1 << 5)) != 0;
        g_avx512f = (cpuInfo[1] & (1 << 16)) != 0;
    }
    g_initialized = true;
}

bool hasAVX2() { if (!g_initialized) initCpuFeatures(); return g_avx2; }
bool hasAVX512F() { if (!g_initialized) initCpuFeatures(); return g_avx512f; }

// --- xxHash64 Simple Implementation (Scalar for now, SIMD in v0.2.0) ---
// Based on xxHash64 algorithm
static const uint64_t PRIME64_1 = 11400714785074694791ULL;
static const uint64_t PRIME64_2 = 14029467366897019727ULL;
static const uint64_t PRIME64_3 = 1609587929392839161ULL;
static const uint64_t PRIME64_4 = 9650029242287828579ULL;
static const uint64_t PRIME64_5 = 2870177450012600261ULL;

static uint64_t rotl64(uint64_t x, int r) {
    return (x << r) | (x >> (64 - r));
}

uint64_t hashXXH64(const uint8_t* data, size_t length, uint64_t seed) {
    uint64_t h64;
    const uint8_t* p = data;
    const uint8_t* const end = data + length;

    if (length >= 32) {
        const uint8_t* const limit = end - 32;
        uint64_t v1 = seed + PRIME64_1 + PRIME64_2;
        uint64_t v2 = seed + PRIME64_2;
        uint64_t v3 = seed + 0;
        uint64_t v4 = seed - PRIME64_1;

        do {
            uint64_t k1, k2, k3, k4;
            memcpy(&k1, p, 8); v1 += k1 * PRIME64_2; v1 = rotl64(v1, 31); v1 *= PRIME64_1; p += 8;
            memcpy(&k2, p, 8); v2 += k2 * PRIME64_2; v2 = rotl64(v2, 31); v2 *= PRIME64_1; p += 8;
            memcpy(&k3, p, 8); v3 += k3 * PRIME64_2; v3 = rotl64(v3, 31); v3 *= PRIME64_1; p += 8;
            memcpy(&k4, p, 8); v4 += k4 * PRIME64_2; v4 = rotl64(v4, 31); v4 *= PRIME64_1; p += 8;
        } while (p <= limit);

        h64 = rotl64(v1, 1) + rotl64(v2, 7) + rotl64(v3, 12) + rotl64(v4, 18);

        v1 *= PRIME64_2; v1 = rotl64(v1, 31); v1 *= PRIME64_1; h64 ^= v1; h64 = h64 * PRIME64_1 + PRIME64_4;
        v2 *= PRIME64_2; v2 = rotl64(v2, 31); v2 *= PRIME64_1; h64 ^= v2; h64 = h64 * PRIME64_1 + PRIME64_4;
        v3 *= PRIME64_2; v3 = rotl64(v3, 31); v3 *= PRIME64_1; h64 ^= v3; h64 = h64 * PRIME64_1 + PRIME64_4;
        v4 *= PRIME64_2; v4 = rotl64(v4, 31); v4 *= PRIME64_1; h64 ^= v4; h64 = h64 * PRIME64_1 + PRIME64_4;
    } else {
        h64 = seed + PRIME64_5;
    }

    h64 += (uint64_t)length;

    while (p + 8 <= end) {
        uint64_t k1; memcpy(&k1, p, 8);
        k1 *= PRIME64_2; k1 = rotl64(k1, 31); k1 *= PRIME64_1; h64 ^= k1;
        h64 = rotl64(h64, 27) * PRIME64_1 + PRIME64_4;
        p += 8;
    }

    if (p + 4 <= end) {
        uint32_t k1; memcpy(&k1, p, 4);
        h64 ^= (uint64_t)k1 * PRIME64_1;
        h64 = rotl64(h64, 23) * PRIME64_2 + PRIME64_3;
        p += 4;
    }

    while (p < end) {
        h64 ^= (uint64_t)(*p) * PRIME64_5;
        h64 = rotl64(h64, 11) * PRIME64_1;
        p++;
    }

    h64 ^= h64 >> 33;
    h64 *= PRIME64_2;
    h64 ^= h64 >> 29;
    h64 *= PRIME64_3;
    h64 ^= h64 >> 32;

    return h64;
}

// --- LZ4 Placeholder (To be replaced by real LZ4 C sources) ---
int compressLZ4(const uint8_t* src, size_t srcSize, uint8_t* dst, size_t dstCapacity) {
    // In v0.1.0 we just use a simple memcpy if LZ4 lib is not yet linked
    // Real implementation would call LZ4_compress_default
    return -1; // Placeholder for now
}

size_t getLZ4MaxCompressedSize(size_t inputSize) {
    return inputSize + (inputSize / 255) + 16;
}

} // namespace fastcompress

// --- JNI Bridge ---
using namespace fastcompress;

extern "C" {

JNIEXPORT jlong JNICALL Java_fastcompress_FastCompress_hash64(JNIEnv* env, jclass, jbyteArray data, jint offset, jint length, jlong seed) {
    void* ptr = env->GetPrimitiveArrayCritical(data, 0);
    uint64_t res = hashXXH64(reinterpret_cast<const uint8_t*>(ptr) + offset, static_cast<size_t>(length), static_cast<uint64_t>(seed));
    env->ReleasePrimitiveArrayCritical(data, ptr, JNI_ABORT);
    return static_cast<jlong>(res);
}

JNIEXPORT jlong JNICALL Java_fastcompress_FastCompress_hash64Direct(JNIEnv* env, jclass, jobject buffer, jint offset, jint length, jlong seed) {
    uint8_t* ptr = reinterpret_cast<uint8_t*>(env->GetDirectBufferAddress(buffer));
    if (!ptr) return 0;
    return static_cast<jlong>(hashXXH64(ptr + offset, static_cast<size_t>(length), static_cast<uint64_t>(seed)));
}

JNIEXPORT jint JNICALL Java_fastcompress_FastCompress_getLZ4MaxCompressedSize(JNIEnv* env, jclass, jint inputSize) {
    return static_cast<jint>(getLZ4MaxCompressedSize(static_cast<size_t>(inputSize)));
}

// Additional JNI methods for LZ4 and Zstd would follow here...
}
