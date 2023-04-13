$(O)/3rdparty/wasm3:
	git clone https://github.com/wasm3/wasm3.git $(O)/3rdparty/wasm3

$(O)/3rdparty-build-wasm/wasm3/lib/libm3.a: $(O)/3rdparty/wasm3
	mkdir -p $(O)/3rdparty-build-wasm/wasm3
	sh $(R)/tools/cmake.sh cmake -S$(O)/3rdparty/wasm3/source -B$(O)/3rdparty-build-wasm/wasm3
	$(MAKE) -C $(O)/3rdparty-build-wasm/wasm3 m3

WASM3_CFLAGS=-I$(O)/3rdparty/wasm3/source -I$(O)/3rdparty/wasm3/platforms/cpp/wasm3_cpp/include

WASM3_LIBS=$(O)/3rdparty-build-wasm/wasm3/lib/libm3.a


$(O)/3rdparty/binaryen:
	git clone https://github.com/WebAssembly/binaryen.git $(O)/3rdparty/binaryen

$(O)/3rdparty-build-wasm/binaryen/lib/libbinaryen.a: $(O)/3rdparty/binaryen
	mkdir -p $(O)/3rdparty-build-wasm/binaryen
	sh $(R)/tools/cmake.sh cmake -DBUILD_TESTS=OFF -DENABLE_WERROR=OFF -DBUILD_TOOLS=OFF -DBUILD_LLVM_DWARF=OFF -DBUILD_STATIC_LIB=ON -S$(O)/3rdparty/binaryen -B$(O)/3rdparty-build-wasm/binaryen
	$(MAKE) -C $(O)/3rdparty-build-wasm/binaryen binaryen

BY_CFLAGS=-I$(O)/3rdparty/binaryen/src

BY_LIBS=$(O)/3rdparty-build-wasm/binaryen/lib/libbinaryen.a

include $(R)/corelib/makefile.mk