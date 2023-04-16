#include <array>
#include <cstdint>
#include <map>
extern std::map<uint64_t, uint8_t> glob;
extern std::map<uint32_t,std::array<uint64_t, 4>> wasi;
extern "C"{
    bool pipe(std::array<uint64_t, 4> &a, std::array<uint64_t, 4> &b, bool twoWay);
    uint64_t readWrite(std::array<uint64_t, 4> a, uint8_t *c, uint64_t cl, bool write);
    bool close(std::array<uint64_t, 4> handle);
}