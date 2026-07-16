# FastCompress (incl. FastHash)

## 1. Vision & Core Idea
**FastCompress** brings native, SIMD-accelerated data operations (Compression and Hashing) to Java.

When an AI agent records hundreds of screenshots (`FastScreen`), collects log files, or needs to manage large JSON states (`FastJSON`), RAM or SSD space fills up quickly.
Java's built-in `java.util.zip` (GZIP/Deflate) is reliable but extremely CPU-intensive and slow.

**The Solution: LZ4 / zstd & xxHash**
- **LZ4:** Compresses data at up to 800 MB/s (decompression at >4 GB/s).
- **Zstandard (zstd):** Significantly better compression than GZIP at many times the speed.
- **xxHash:** A blazingly fast non-cryptographic hash algorithm (working at the limit of RAM bandwidth, ~15 GB/s) to check if a screenshot or data block has changed.

## 2. Java High-Level API

```java
public interface FastCompress {
    static FastCompress open() { return new FastCompressImpl(); }

    // LZ4 Compression
    int compressLZ4(byte[] src, byte[] dest);
    int decompressLZ4(byte[] src, byte[] dest, int uncompressedSize);

    // Zstd Compression (for higher ratios)
    int compressZstd(byte[] src, byte[] dest, int compressionLevel);

    // High-speed SIMD Hashing
    long hashXXH64(byte[] data);
    long hashXXH64(long nativePointer, int length);
}
```

## 3. C++ JNI Backend
The backend consists of highly optimized C libraries passed through via JNI.

1. **LZ4 / Zstd Core:** Integration of raw C implementations. The libraries utilize intrinsic AVX2/SIMD instructions of modern CPUs.
2. **Zero-Copy Arrays:** Instead of using `GetByteArrayElements` (which can create a copy), FastCompress uses `GetPrimitiveArrayCritical` or works directly on `DirectByteBuffer` / native pointers (from `FastSharedMemory`) to completely eliminate copy operations between the JVM and C++.
3. **xxHash:** Uses the 64-bit or 128-bit vector implementation of xxHash, for example, to determine in `FastScreen` within 0.1 milliseconds whether the current frame is exactly identical to the previous one (saving CPU/GPU time).

## 4. Agent-Kit (AI Integration)
For the agent, this is primarily an infrastructure tool.

- **State-Caching:** Saves the state of the agent (memory, UI trees) as a Zstd-compressed block to halve boot times.
- **Visual Diffing:** Before the agent sends an image to the LLM, it hashes it (`hashXXH64`). If the hash is the same as 1 second ago, it doesn't send a request (saving token costs and time).
