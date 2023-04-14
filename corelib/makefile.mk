$(O)/corelib/corelib.wasm: $(R)/corelib/*.cc $(O)/3rdparty-build-wasm/wasm3/lib/libm3.a $(O)/3rdparty-build-wasm/binaryen/lib/libbinaryen.a $(R)/corelib/*.h $(O)/ject/ject.wasm.h
	mkdir -p $(O)/corelib
	sh $(R)/tools/k++ -std=c++2a $(WASM3_CFLAGS) $(BY_CFLAGS) -I$(O)/ject -I$(R)/corelib -o $@ $<