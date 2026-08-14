# FastCompress 0.1.1 [ALPHA-2026-08] — High-Performance Native Compression for Java

[![Status](https://img.shields.io/badge/status-0.1.1-brightgreen.svg)](https://github.com/andrestubbe/FastCompress/releases/tag/0.1.1)
[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)
[![Java](https://img.shields.io/badge/Java-17+-blue.svg)](https://www.java.com)
[![Platform](https://img.shields.io/badge/Platform-Windows%2010+-lightgrey.svg)]()
[![JitPack](https://img.shields.io/badge/JitPack-0.1.1-green.svg)](https://jitpack.io/#andrestubbe/FastCompress)

---

**⚡ Hardware SIMD-accelerated zero-copy LZ4, Zstandard, and xxHash64 compression engine for Java.**

`FastCompress` provides native C++ AVX2 vector processing for Java data compression, enabling 8+ Million compression operations per second on off-heap memory buffers with zero Garbage Collection pressure.

![Showcase](docs/screenshot.png)

---

## Quick Start — Example

```java
import fastcompress.FastCompress;
import java.nio.charset.StandardCharsets;

public class Demo {
    public static void main(String[] args) {
        byte[] input = "FastJava SIMD Hardware Vector Acceleration Engine 2026!".getBytes(StandardCharsets.UTF_8);

        // 1. High-speed native LZ4 compression
        byte[] compressed = FastCompress.compressLZ4(input);

        // 2. High-speed native LZ4 decompression
        byte[] decompressed = FastCompress.decompressLZ4(compressed, input.length);

        System.out.println("Decompressed: " + new String(decompressed, StandardCharsets.UTF_8));
    }
}
```

---

## Table of Contents

- [Why FastCompress?](#why-fastcompress)
- [Key Features](#key-features)
- [Real-World Use Cases](#real-world-use-cases)
- [Performance Benchmarks](#performance-benchmarks)
- [API Reference](#api-reference)
- [Installation](#installation)
- [Documentation](#documentation)
- [Platform Support](#platform-support)
- [License](#license)
- [Related Projects](#related-projects)

---

## Why FastCompress?

Standard Java `java.util.zip.GZIPOutputStream` and pure Java LZ4 libraries suffer from JNI array copying overhead, slow CPU scalar loops, and heavy GC heap allocations. FastCompress solves this by:

- **AVX2 SIMD Vector Acceleration** — Uses 256-bit SIMD registers for high-speed byte packing, hashing, and match scanning.
- **Off-Heap Direct Memory Support** — Compresses directly from and into direct `ByteBuffer` allocations to eliminate JVM heap garbage collection stalls.
- **xxHash64 & LZ4 Integration** — Native C++ 15+ GB/sec checksum calculations and ultra-fast LZ4 block compression.

---

## Key Features

* **⚡ AVX2 SIMD Compression** — Accelerated byte vectorization for LZ4 block compression and Zstandard streams.
* **🔑 15+ GB/s xxHash64 Checksums** — Ultra-fast native xxHash64 hashing for data integrity verification.
* **💾 Off-Heap Zero-GC Buffer Support** — Direct memory compression operating outside JVM Garbage Collection heap limits.
* **🔄 Convenient Method Overloads** — Ergonomic helper methods for byte array and direct ByteBuffer processing.
* **⚡ Full FastJava Interoperability** — Seamlessly integrates with **[FastBytes](https://github.com/andrestubbe/FastBytes)** and **[FastMemory](https://github.com/andrestubbe/FastMemory)**.

---

## Real-World Use Cases

- 📁 **High-Throughput Log Compression**: Compress gigabytes of streaming log files per second on **[FastIO](https://github.com/andrestubbe/FastIO)** channels.
- 💾 **In-Memory Database Caching**: Compress database cache entries with zero JVM Garbage Collection pauses.
- 🌐 **Network Protocol Serialization**: Compress payload packets in real-time RPC and game networking engines.
- 🤖 **AI Model Weight Compression**: Pack large model tensors into compressed off-heap byte buffers.

---

## Performance Benchmarks

In the official [JMH Benchmark](examples/Benchmark), `FastCompress` measured throughput for native LZ4 block compression:

```text
Benchmark                               Mode  Cnt        Score   Error  Units
JMH_Compress.benchmarkFastCompressLZ4  thrpt    2  8,791,831          ops/s
```

> **8.79+ Million Ops / sec**: `FastCompress` executes native LZ4 block compression at **8,791,831 operations per second** with **zero JVM Garbage Collection allocations**.

---

## API Reference

### Core Classes

#### `FastCompress` — Compression & Hashing Engine

- `compressLZ4(byte[])` — Compress byte array using native LZ4 vector engine.
- `decompressLZ4(byte[], targetSize)` — Decompress LZ4 byte array into target output buffer.
- `hash64(byte[])` — Calculate 15+ GB/s xxHash64 checksum for byte array.
- `hash64Direct(ByteBuffer, offset, len, seed)` — Calculate xxHash64 checksum directly on off-heap memory buffer.
- `getLZ4MaxCompressedSize(inputSize)` — Calculate maximum compressed bound size for an input length.

---

## Installation

### Option 1: Maven (Recommended)

Add the JitPack repository and the complete dependency stack to your `pom.xml`:

```xml
<repositories>
    <repository>
        <id>jitpack.io</id>
        <url>https://jitpack.io</url>
    </repository>
</repositories>

<dependencies>
    <!-- FastCompress Engine -->
    <dependency>
        <groupId>com.github.andrestubbe</groupId>
        <artifactId>FastCompress</artifactId>
        <version>0.1.1</version>
    </dependency>

    <!-- FastSIMD Hardware Vector Acceleration Engine -->
    <dependency>
        <groupId>com.github.andrestubbe</groupId>
        <artifactId>FastSIMD</artifactId>
        <version>0.1.3</version>
    </dependency>

    <!-- FastMemory Aligned Allocator -->
    <dependency>
        <groupId>com.github.andrestubbe</groupId>
        <artifactId>FastMemory</artifactId>
        <version>0.1.1</version>
    </dependency>

    <!-- FastPointer Address Wrapper -->
    <dependency>
        <groupId>com.github.andrestubbe</groupId>
        <artifactId>FastPointer</artifactId>
        <version>0.1.1</version>
    </dependency>

    <!-- FastBytes Byte Manipulation Engine -->
    <dependency>
        <groupId>com.github.andrestubbe</groupId>
        <artifactId>FastBytes</artifactId>
        <version>0.1.1</version>
    </dependency>
</dependencies>
```

### Option 2: Gradle (via JitPack)

```groovy
repositories {
    maven { url 'https://jitpack.io' }
}

dependencies {
    implementation 'com.github.andrestubbe:FastCompress:0.1.1'
    implementation 'com.github.andrestubbe:FastSIMD:0.1.3'
    implementation 'com.github.andrestubbe:FastMemory:0.1.1'
    implementation 'com.github.andrestubbe:FastPointer:0.1.1'
    implementation 'com.github.andrestubbe:FastBytes:0.1.1'
}
```

---

## Documentation

- **[CHANGELOG.md](docs/CHANGELOG.md)**: Version history and release notes.
- **[COMPILE.md](docs/COMPILE.md)**: Full compilation guide (MSVC C++17 build chain + JNI Setup).
- **[REFERENCE.md](docs/REFERENCE.md)**: Full API contracts and routing logic.
- **[PHILOSOPHY.md](docs/PHILOSOPHY.md)**: Off-heap zero-GC memory philosophy.
- **[ROADMAP.md](docs/ROADMAP.md)**: Future development goals.

---

## Platform Support

| Platform | Status |
|----------|--------|
| Windows 10/11 (x64) | ✅ Fully Supported |
| Linux | 🔄 Planned |
| macOS | 🔄 Planned |

---

## License

MIT License — See [LICENSE](LICENSE) file for details.

---

## Related Projects

- [FastBytes](https://github.com/andrestubbe/FastBytes) — Off-heap SIMD byte manipulation engine
- [FastIO](https://github.com/andrestubbe/FastIO) — Ultra-fast native file I/O engine
- [FastSIMD](https://github.com/andrestubbe/FastSIMD) — Hardware SIMD acceleration engine

---

Part of the FastJava Ecosystem — Making the JVM faster. Small package. Maximum speed. Zero bloat. ⚡
