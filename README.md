# FastCompress â€” Ultra-Fast Native Compression for Java [v0.1.0]

**A high-performance native compression and hashing module for the FastJava ecosystem. Optimized for raw throughput and SIMD-accelerated algorithms.**

[![Status](https://img.shields.io/badge/status-v0.1.0--alpha-orange.svg)]()
[![Java](https://img.shields.io/badge/Java-17+-blue.svg)](https://www.java.com)
[![Platform](https://img.shields.io/badge/Platform-Windows%2010+-lightgrey.svg)]()
[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)

---

**FastCompress** delivers elite compression performance by leveraging native SIMD instructions and optimized memory handling. Built for high-throughput data pipelines, real-time telemetry, and agentic state management.

```java
// Quick Start â€” SIMD Hashing
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
-   **âš¡ SIMD Accelerated** â€” LZ4 and xxHash paths tuned for AVX2/AVX-512.
-   **ðŸ” Change Detection** â€” Sub-millisecond hashing for visual diffing.
-   **ðŸš€ Zero-Copy** â€” Direct memory access via JNI critical sections.
-   **ðŸ“¦ Minimal Footprint** â€” Designed for low-latency agentic substrate.

---

## ðŸ“Š Performance (v0.1.0 Alpha)
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
| `hash64(data)` | High-speed xxHash64 checksum. | [Reference â†’](REFERENCE.md#hashing) |
| `compressLZ4(...)` | Fastest block compression. | [Reference â†’](REFERENCE.md#lz4) |
| `compressZstd(...)` | High-efficiency compression. | [Reference â†’](REFERENCE.md#zstd) |

---

## Installation

### Option 1: Maven (Recommended)
Add the JitPack repository and the dependencies to your `pom.xml`:

```xml
<repositories>
    <repository>
        <id>jitpack.io</id>
        <url>https://jitpack.io</url>
    </repository>
</repositories>

<dependencies>
    <!-- FastCompress Library -->
    <dependency>
        <groupId>com.github.andrestubbe</groupId>
        <artifactId>fastcompress</artifactId>
        <version>v0.1.0</version>
    </dependency>

    <!-- FastCore (Required Native Loader) -->
    <dependency>
        <groupId>com.github.andrestubbe</groupId>
        <artifactId>fastcore</artifactId>
        <version>v0.1.0</version>
    </dependency>
</dependencies>
```

### Option 2: Gradle (via JitPack)
```groovy
repositories {
    maven { url 'https://jitpack.io' }
}

dependencies {
    implementation 'com.github.andrestubbe:fastcompress:v0.1.0'
    implementation 'com.github.andrestubbe:fastcore:v0.1.0'
}
```

### Option 3: Direct Download (No Build Tool)
Download the latest JARs directly to add them to your classpath:

1. 📦 **[fastcompress-v0.1.0.jar](https://github.com/andrestubbe/FastCompress/releases/download/v0.1.0/fastcompress-v0.1.0.jar)** (The Core Library)
2. ⚙️ **[fastcore-v0.1.0.jar](https://github.com/andrestubbe/FastCore/releases/download/v0.1.0/fastcore-v0.1.0.jar)** (The Mandatory Native Loader)

> [!IMPORTANT]
> All JARs must be in your classpath for the native JNI calls to function correctly.


## Hero Demos
See the `examples/` directory for high-speed races:
-   **[HashRace.java](examples/src/main/java/fastcompress/HashRace.java)** â€” 10GB Data Checksum Battle.
-   **[CompressRace.java](examples/src/main/java/fastcompress/CompressRace.java)** â€” LZ4 vs GZIP Throughput.

---

## Documentation
*   **[REFERENCE.md](REFERENCE.md)**: JNI contracts and CPU fallback rules.
*   **[PHILOSOPHIE.md](PHILOSOPHIE.md)**: The "Zero-Copy" philosophy.
*   **[ROADMAP.md](ROADMAP.md)**: Future features and AVX-512 plans.

---

## License
MIT License â€” See [LICENSE](LICENSE) file for details.

---

**Part of the FastJava Ecosystem** â€” *Making the JVM faster.*

Made with âš¡ by Andre Stubbe
