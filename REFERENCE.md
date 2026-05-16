# FastCompress Reference

## 1. Supported Algorithms

| Algorithm | Type | Target Speed | Use Case |
|-----------|------|--------------|----------|
| **LZ4**   | Lossless | > 800 MB/s | Real-time streaming, IPC |
| **Zstd**  | Lossless | High Ratio | State persistence, logs |
| **xxHash64**| Hashing | > 15 GB/s | Change detection, checksums |

## 2. CPU Feature Model
FastCompress utilizes runtime dispatching to select the optimal implementation:
*   **AVX-512** — Ultra-wide vectorization for hashing and block processing.
*   **AVX2** — Standard high-performance path for modern x64.
*   **SSE4.2** — Fallback for older hardware.
*   **Scalar** — Guaranteed fallback for maximum compatibility.

## 3. JNI & Memory Contracts
*   **Zero-Copy Memory Pinning**: Uses `GetPrimitiveArrayCritical` to prevent JVM copies during compression/hashing.
*   **Direct Access**: Full support for `java.nio.ByteBuffer` (Direct) for integration with `FastIO` and `FastSharedMemory`.
*   **Thread-Safety**: All native methods are stateless and thread-safe.

## 4. Guarantees
*   **No Allocation**: The compression methods do not allocate memory on the Java heap during execution (except for the result arrays if not provided).
*   **Unaligned Access**: Safe for all memory boundaries (internally handled by native layer).

## 5. API Preview (v0.1.0)
```java
// Block Compression
int compressLZ4(byte[] src, byte[] dst);
int compressZstd(byte[] src, byte[] dst, int level);

// SIMD Hashing
long hash64(byte[] data);
long hash64(ByteBuffer directBuffer);
```

---
**Part of the FastJava Ecosystem** — *Making the JVM faster.*

Made with ⚡ by Andre Stubbe
