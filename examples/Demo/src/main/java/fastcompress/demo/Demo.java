package fastcompress.demo;

import fastcompress.FastCompress;
import java.nio.charset.StandardCharsets;

public class Demo {
    public static void main(String[] args) {
        System.out.println("--- FastCompress 0.1.1 Demo ---");
        byte[] input = "FastJava SIMD Hardware Vector Acceleration Engine 2026!".getBytes(StandardCharsets.UTF_8);
        
        byte[] compressed = FastCompress.compressLZ4(input);
        byte[] decompressed = FastCompress.decompressLZ4(compressed, input.length);
        
        System.out.printf("Original Size: %d bytes | Compressed: %d bytes%n", input.length, compressed.length);
        System.out.println("Decompressed: " + new String(decompressed, StandardCharsets.UTF_8));
        System.out.println("✔ FastCompress demo completed.");
    }
}
