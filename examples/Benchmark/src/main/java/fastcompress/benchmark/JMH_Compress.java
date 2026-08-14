package fastcompress.benchmark;

import fastcompress.FastCompress;
import org.openjdk.jmh.annotations.*;

import java.nio.charset.StandardCharsets;
import java.util.concurrent.TimeUnit;

@State(Scope.Thread)
@BenchmarkMode(Mode.Throughput)
@OutputTimeUnit(TimeUnit.SECONDS)
public class JMH_Compress {

    private byte[] input;

    @Setup
    public void setup() {
        input = "FastJava SIMD Hardware Vector Acceleration Engine 2026! High performance LZ4 native compression.".getBytes(StandardCharsets.UTF_8);
    }

    @Benchmark
    public byte[] benchmarkFastCompressLZ4() {
        return FastCompress.compressLZ4(input);
    }
}
