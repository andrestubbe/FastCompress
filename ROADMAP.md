# FastCompress Roadmap 🗺️

**Vision:** To provide the fastest possible native compression and hashing primitives for Java, enabling zero-latency state management for AI agents.

## 🟢 v0.1.0: Foundation Release (Current)
- [ ] **Core Native Engine**: Integration of LZ4 and xxHash64 C++ sources.
- [ ] **Blueprint Standards**: Implementation of README, Reference, and Philosophy.
- [ ] **Basic JNI Bridge**: Support for `byte[]` and `DirectByteBuffer`.
- [ ] **Initial Benchmarks**: Comparison vs `java.util.zip.CRC32` and `Deflater`.

## 🟡 v0.2.0: FastIO Hardening & Foundation
- [ ] **FastIO Substrate**: Complete FastIO hardening (Async I/O, IoRing support)
- [ ] **Package Flattening**: Migrate from `io.github.andrestubbe.fastcompress` to `fastcompress.*`
- [ ] **Premium Documentation**: PHILOSOPHIE.md (SIMD Compression & Hashing), REFERENCE.md (LZ4, Zstd, xxHash contracts)
- [ ] **Hero Demo**: Create "1GB Read/Write Race" demo for FastIO

## 🟠 v0.5.0: Core Implementation (Nitro Engine)
- [ ] **Native Backend**: Integrate LZ4 (Raw C + SIMD), Zstandard (zstd), xxHash (AVX2/AVX-512)
- [ ] **Zero-Copy JNI**: Implement `GetPrimitiveArrayCritical` paths and `DirectByteBuffer` native pointer access
- [ ] **Performance Benchmarks**: JMH micro-benchmarks vs `java.util.zip`
- [ ] **Hero Demo**: Real-Time Screenshot Diffing @ 10GB/s
- [ ] **Streaming API**: Native-backed `InputStream`/`OutputStream` wrappers
- [ ] **Dictionary Training**: Support for Zstd dictionaries to optimize small JSON states

## 🔴 v1.0.0: Production Hardening
- [ ] **Stress Testing**: Long-running memory leak and stability audits.
- [ ] **NUMA Awareness**: Optimization for large-scale enterprise servers.

---
**Focus:** Speed is the only metric that matters.

**Part of the FastJava Ecosystem** — *Making the JVM faster.*
