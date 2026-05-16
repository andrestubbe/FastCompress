# FastCompress — Ultra-Fast Native Compression for Java [v0.1.0]

**A high-performance native compression and hashing module for the FastJava ecosystem. Optimized for raw throughput and SIMD-accelerated algorithms.**

[![Status](https://img.shields.io/badge/status-v0.1.0--alpha-orange.svg)]()
[![Java](https://img.shields.io/badge/Java-17+-blue.svg)](https://www.java.com)
[![Platform](https://img.shields.io/badge/Platform-Windows%2010+-lightgrey.svg)]()
[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)

---

**FastCompress** delivers elite compression performance by leveraging native SIMD instructions and optimized memory handling. Built for high-throughput data pipelines, real-time telemetry, and agentic state management.

```java
// Quick Start — SIMD Hashing
byte[] data = ...; 
long hash = FastCompress.hash64(data); // 15 GB/s throughput
```

## Table of Contents
- [Key Features](#key-features)
- [Performance](#performance)
- [API Quick Reference](#api-quick-reference)
- [Installation](#installation)
- [Hero Demos](#hero-demos)
- [Documentation](#documentation)
- [Platform Support](#platform-support)
- [License](#license)

---

## Key Features
-   **⚡ SIMD Accelerated** — LZ4 and xxHash paths tuned for AVX2/AVX-512.
-   **🔍 Change Detection** — Sub-millisecond hashing for visual diffing.
-   **🚀 Zero-Copy** — Direct memory access via JNI critical sections.
-   **📦 Minimal Footprint** — Designed for low-latency agentic substrate.

---

## 📊 Performance (v0.1.0 Alpha)
*Measured on Modern x64 Hardware.*

| Operation | Standard Java | FastCompress Native | Speedup |
|-----------|---------------|--------------------|---------|
| **Hashing** (1GB) | ~500 ms (CRC32) | **~65 ms** (xxHash64) | **7.7x** |
| **Compression** (1GB) | ~2200 ms (GZIP) | **~240 ms** (LZ4) | **9.1x** |

> [!NOTE]
> Read the full performance manifest in **[PHILOSOPHIE.md](./PHILOSOPHIE.md)**.

---

## API Quick Reference

| Method | Description | Documentation |
|--------|-------------|---------------|
| `hash64(data)` | High-speed xxHash64 checksum. | [Reference →](REFERENCE.md#hashing) |
| `compressLZ4(...)` | Fastest block compression. | [Reference →](REFERENCE.md#lz4) |
| `compressZstd(...)` | High-efficiency compression. | [Reference →](REFERENCE.md#zstd) |

---

## Installation

### Maven (JitPack)
```xml
<dependencies>
    <dependency>
        <groupId>com.github.andrestubbe</groupId>
        <artifactId>fastcompress</artifactId>
        <version>v0.1.0</version>
    </dependency>
    <dependency>
        <groupId>com.github.andrestubbe</groupId>
        <artifactId>fastcore</artifactId>
        <version>v0.1.0</version>
    </dependency>
</dependencies>
```

---

## Hero Demos
See the `examples/` directory for high-speed races:
-   **[HashRace.java](examples/src/main/java/fastcompress/HashRace.java)** — 10GB Data Checksum Battle.
-   **[CompressRace.java](examples/src/main/java/fastcompress/CompressRace.java)** — LZ4 vs GZIP Throughput.

---

## Documentation
*   **[REFERENCE.md](REFERENCE.md)**: JNI contracts and CPU fallback rules.
*   **[PHILOSOPHIE.md](PHILOSOPHIE.md)**: The "Zero-Copy" philosophy.
*   **[ROADMAP.md](ROADMAP.md)**: Future features and AVX-512 plans.

---

## License
MIT License — See [LICENSE](LICENSE) file for details.

---

**Part of the FastJava Ecosystem** — *Making the JVM faster.*

Made with ⚡ by Andre Stubbe
