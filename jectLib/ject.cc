#include "ject.h"
#include "jectglobals.h"
#include <array>
#include <cstddef>
#include <cstdint>
typedef struct wasi_iovec_t {
  /**
   * The address of the buffer to be filled.
   */
  uint64_t buf;

  /**
   * The length of the buffer to be filled.
   */
  size_t buf_len;

} wasi_iovec_t;

std::map<uint64_t, uint8_t> glob;
std::map<uint32_t, std::array<uint64_t, 4>> wasi;
extern "C" {
uint32_t mo_load_i32(uint64_t a) { return sget<uint32_t>(glob, a); }
uint64_t mo_load_i64(uint64_t a) { return sget<uint64_t>(glob, a); }
float mo_load_f32(uint64_t a) { return sget<float>(glob, a); }
double mo_load_f64(uint64_t a) { return sget<double>(glob, a); }

void mo_store_i32(uint64_t a, uint32_t b) { sput(glob, a, b); }
void mo_store_i64(uint64_t a, uint64_t b) { sput(glob, a, b); }
void mo_store_f32(uint64_t a, float b) { sput(glob, a, b); }
void mo_store_f64(uint64_t a, double b) { sput(glob, a, b); }

void mo$wasi_snapshot_preview1$fd_read(uint32_t a, uint64_t p, size_t l,
                                       uint64_t t) {
  for (size_t i = 0; i < l; i++) {
    auto r =
        sget<wasi_iovec_t>(glob, p + (i * sizeof(struct wasi_iovec_t)));
    uint8_t x[r.buf_len];
    auto y = readWrite(wasi[a], &x[0], r.buf_len, false);
    if (y) {
      mo_store_i32(t, y);
      return;
    }
    for (size_t b = 0; b < r.buf_len; b++)
      glob[r.buf + b] = x[b];
  }
  mo_store_i32(t, 0);
}
void mo$wasi_snapshot_preview1$fd_pread(uint32_t a, uint64_t p, size_t l,
                                        uint64_t t) {
  for (size_t i = 0; i < l; i++) {
    auto r =
        sget<wasi_iovec_t>(glob, p + (i * sizeof(struct wasi_iovec_t)));
    uint8_t x[r.buf_len];
    auto y = readWrite(wasi[a], &x[0], r.buf_len, false);
    if (y) {
      mo_store_i32(t, y);
      return;
    }
    for (size_t b = 0; b < r.buf_len; b++)
      glob[r.buf + b] = x[b];
  }
  mo_store_i32(t, 0);
}
void mo$wasi_snapshot_preview1$fd_write(uint32_t a, uint64_t p, size_t l,
                                        uint64_t t) {
  for (size_t i = 0; i < l; i++) {
    auto r =
        sget<wasi_iovec_t>(glob, p + (i * sizeof(struct wasi_iovec_t)));
    uint8_t x[r.buf_len];
    for (size_t b = 0; b < r.buf_len; b++)
      x[b] = glob[r.buf + b];
    auto y = readWrite(wasi[a], &x[0], r.buf_len, true);
    if (y) {
      mo_store_i32(t, y);
      return;
    }
  }
  mo_store_i32(t, 0);
}

uint32_t mo$wasi_snapshot_preview1$path_open(uint32_t a, uint32_t b_,
                                             uint64_t c, size_t d, int32_t arg4,
                                             int64_t arg5, int64_t arg6,
                                             int32_t arg7, uint64_t t) {
  auto y = readWrite(wasi[a], (uint8_t *)"o", 1, true);
  if (y) {
    return y;
  }
  uint8_t x[d];
  for (size_t e = 0; e < d; e++)
    x[e] = glob[c + e];
  y = readWrite(wasi[a], &x[0], d, true);
  if (y) {
    return y;
  }
  y = readWrite(wasi[a], (uint8_t *)"\0", 1, true);
  if (y) {
    return y;
  }
  uint8_t z[32];
  y = readWrite(wasi[a], &z[0], 32, false);
  if (y) {
    return y;
  }
  uint32_t j;
  alloc<std::array<uint64_t, 4>, uint32_t>(wasi, &j) =
      dearrize<std::array<uint64_t, 4>>(std::to_array(z));
  mo_store_i32(t, j);
}
}