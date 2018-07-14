
# gcc -m32
#	resolve Error: unsupported instruction `mov', force to build 32-bit ABI to make build success.
# ld -m elf_i386
#	resolve ld: i386 architecture of input file `TinyHelloWorld.o' is incompatible with i386:x86-64 output,
#	use 32-bit elf instead.
TinyHelloWorld: TinyHelloWorld.c
	gcc -c -fno-builtin -m32 TinyHelloWorld.c
	ld -static -m elf_i386 -e nomain -o TinyHelloWorld TinyHelloWorld.o

TinyHelloWorldByLds: TinyHelloWorld.c
	gcc -c -fno-builtin -m32 TinyHelloWorld.c
	ld -static -m elf_i386 -T TinyHelloWorld.lds -o TinyHelloWorldByLds TinyHelloWorld.o

clean:
	rm TinyHelloWorld.o TinyHelloWorld TinyHelloWorldByLds
