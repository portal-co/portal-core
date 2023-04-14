#include "ject.h"
#include "jectglobals.h"
#include <cstdint>
std::map<uint64_t, uint8_t> glob;
extern "C" {
uint32_t mo_load_i32(uint64_t a) { return sget<uint32_t>(glob, a); }
uint64_t mo_load_i64(uint64_t a) { return sget<uint64_t>(glob, a); }
float mo_load_f32(uint64_t a) { return sget<float>(glob, a); }
double mo_load_f64(uint64_t a) { return sget<double>(glob, a); }

void mo_store_i32(uint64_t a, uint32_t b) { sput(glob, a, b); }
void mo_store_i64(uint64_t a, uint64_t b) { sput(glob, a, b); }
void mo_store_f32(uint64_t a, float b) { sput(glob, a, b); }
void mo_store_f64(uint64_t a, double b) { sput(glob, a, b); }
}