# FastCompress API Reference Manual

`FastCompress` provides native C++ AVX2 vector compression, LZ4 block compression, and xxHash64 checksum calculators.

---

## 1. LZ4 Compression API

### `compressLZ4`
```java
public static byte[] compressLZ4(byte[] src)
public static native int compressLZ4(byte[] src, int srcPos, int length, byte[] dest, int destPos)
```
Compresses input byte buffer using high-speed native LZ4 algorithms.

---

### `decompressLZ4`
```java
public static byte[] decompressLZ4(byte[] src, int targetSize)
public static native int decompressLZ4(byte[] src, int srcPos, int length, byte[] dest, int destPos, int targetSize)
```
Decompresses LZ4 compressed buffer into target output buffer.

---

## 2. xxHash64 Hashing API

### `hash64`
```java
public static long hash64(byte[] data)
public static native long hash64(byte[] data, int offset, int length, long seed)
public static native long hash64Direct(ByteBuffer buffer, int offset, int length, long seed)
```
Calculates 15+ GB/s xxHash64 checksum across byte arrays or direct off-heap ByteBuffers.
