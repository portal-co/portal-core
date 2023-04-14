#include "map.h"
#include "wasm-binary.h"
#include "wasm3_cpp.h"
#include "wasm3h.h"
inline wasm3::module load(wasm::Module *x, wasm3::environment e) {
  wasm::BufferWithRandomAccess b;
  wasm::WasmBinaryWriter w(x, b);
  w.write();
  return e.parse_module(&b[0], b.size());
}
template <typename F>
wasm::BufferWithRandomAccess viaModule(std::vector<uint8_t> x,
                                       wasm::FeatureSet &f, F fn) {
  wasm::BufferWithRandomAccess r;
  wasm::Module m;
  wasm::WasmBinaryBuilder b(m, f,
                            map(x, [](auto i,auto x) -> char { return (char)x; }));
  b.read();
  fn(&m);
  wasm::WasmBinaryWriter w(&m, r);
  w.write();
  f = m.features;
  return r;
}
template <typename F>
wasm3::module load_transformed(wasm3::environment e, std::vector<uint8_t> x,
                               wasm::FeatureSet &f, F fn) {
  auto j = viaModule(x, f, fn);
  return e.parse_module(&j[0], j.size());
}