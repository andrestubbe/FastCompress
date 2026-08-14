package fastcompress;

import fastcore.FastCore;
import java.nio.ByteBuffer;

/**
 * High-performance native compression and hashing engine.
 * Powered by LZ4, Zstandard, and xxHash with SIMD acceleration.
 */
public final class FastCompress {

    static {
        FastCore.loadLibrary("fastcompress");
    }

    // Prevent instantiation
    private FastCompress() {}

    /**
     * Calculates the xxHash64 checksum of a byte array.
     * Throughput: > 15 GB/s on modern hardware.
     */
    public static native long hash64(byte[] data, int offset, int length, long seed);

    /**
     * Calculates the xxHash64 checksum of a byte array with default seed (0).
     */
    public static long hash64(byte[] data) {
        return hash64(data, 0, data.length, 0);
    }

    /**
     * Calculates the xxHash64 checksum of a Direct ByteBuffer.
     */
    public static native long hash64Direct(ByteBuffer buffer, int offset, int length, long seed);

    /**
     * Compresses a block of data using LZ4.
     * @param src Source data
     * @param srcPos Source starting position
     * @param length Number of bytes to compress
     * @param dest Destination buffer (must be large enough)
     * @param destPos Destination starting position
     * @return The number of bytes written to dest, or a negative value if compression failed.
     */
    public static native int compressLZ4(byte[] src, int srcPos, int length, byte[] dest, int destPos);

    /**
     * Convenient overload: Compresses a byte array using LZ4 and returns compressed buffer.
     */
    public static byte[] compressLZ4(byte[] src) {
        int maxCompressedSize = getLZ4MaxCompressedSize(src.length);
        byte[] dest = new byte[maxCompressedSize];
        int compressedLen = compressLZ4(src, 0, src.length, dest, 0);
        if (compressedLen < 0) return src;
        byte[] result = new byte[compressedLen];
        System.arraycopy(dest, 0, result, 0, compressedLen);
        return result;
    }

    /**
     * Decompresses an LZ4 compressed block.
     */
    public static native int decompressLZ4(byte[] src, int srcPos, int length, byte[] dest, int destPos, int targetSize);

    /**
     * Convenient overload: Decompresses an LZ4 compressed byte array into targetSize output buffer.
     */
    public static byte[] decompressLZ4(byte[] src, int targetSize) {
        byte[] dest = new byte[targetSize];
        decompressLZ4(src, 0, src.length, dest, 0, targetSize);
        return dest;
    }

    /**
     * Returns the maximum possible size that an LZ4 compressed block can take for a given input size.
     */
    public static native int getLZ4MaxCompressedSize(int inputSize);

    /**
     * Compresses a block of data using Zstandard.
     * @param compressionLevel 1 (fastest) to 22 (best)
     */
    public static native int compressZstd(byte[] src, int srcPos, int length, byte[] dest, int destPos, int compressionLevel);

    /**
     * Decompresses a Zstandard block.
     */
    public static native int decompressZstd(byte[] src, int srcPos, int length, byte[] dest, int destPos, int targetSize);
}
