# FastCompress — Implementation TODO 📋

This TODO tracks the evolution of **FastCompress** from a basic module to a **Premium FastJava Nitro** module, following the standards established by `FastBytes`.

## 🔴 Phase 1: Prerequisite — FastIO Hardening
*Before finishing FastCompress, the data substrate must be ready.*
- [ ] **Blueprint Alignment**: Move `FastIO` to the "Premium" documentation standard.
    - [ ] Create `PHILOSOPHIE.md` (Native-First I/O).
    - [ ] Create `REFERENCE.md` (JNI contracts & fallback rules).
    - [ ] Create `ROADMAP.md` (Async I/O, IoRing support).
- [ ] **Hero Demo**: Create a "1GB Read/Write Race" demo for `FastIO`.

## 🟡 Phase 2: FastCompress Foundation
- [ ] **Package Flattening**: Migrate from `io.github.andrestubbe.fastcompress` to `fastcompress.*`.
- [ ] **Premium Documentation Suite**:
    - [ ] Initialize `PHILOSOPHIE.md` (SIMD Compression & Hashing).
    - [ ] Initialize `REFERENCE.md` (LZ4, Zstd, xxHash contracts).
    - [ ] Initialize `ROADMAP.md` (Multi-threaded compression, streaming).
- [ ] **Ecosystem Sync**: Ensure `pom.xml` and `FastCore` loading match the `FastBytes` v0.1.0 standard.

## 🟢 Phase 3: Core Implementation (Nitro Engine)
- [ ] **Native Backend**:
    - [ ] Integrate LZ4 (Raw C + SIMD).
    - [ ] Integrate Zstandard (zstd).
    - [ ] Integrate xxHash (AVX2/AVX-512).
- [ ] **Zero-Copy JNI**:
    - [ ] Implement `GetPrimitiveArrayCritical` paths.
    - [ ] Implement `DirectByteBuffer` native pointer access.
- [ ] **Performance Benchmarks**:
    - [ ] Add JMH micro-benchmarks vs `java.util.zip`.
    - [ ] Create a "Hero Demo" (e.g., *Real-Time Screenshot Diffing @ 10GB/s*).

## 📊 Success Metrics
| Operation | Goal (vs Standard Java) |
|-----------|-------------------------|
| LZ4 Comp  | 10-20x Speedup          |
| Hashing   | 50x+ Speedup            |
| Memory    | 0 Allocations in Hotpath|

---
**Status:** ⏳ On Hold — Finishing `FastIO` substrate first.
