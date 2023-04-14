$(O)/ject/ject.wasm: $(R)/jectLib/*.cc $(R)/jectLib/*.h
	mkdir -p $(O)/ject
	sh $(R)/tools/k++ -std=c++2a -I$(R)/ject -o $@ $<

$(O)/ject/ject.wasm.h: $(O)/ject/ject.wasm $(O)/tools/embedfile
	$(O)/tools/embedfile $(O)/ject/ject.wasm.h ject $(O)/ject/ject.wasm 