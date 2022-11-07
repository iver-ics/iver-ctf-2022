.PHONY: all
all: program flag.txt bin/nulldev-dbg-symbols.debug

bin:
	mkdir -p bin

bin/nulldev-dbg: src/nulldev.c bin
	clang src/nulldev.c -o bin/nulldev-dbg -g3 -static

bin/nulldev: bin/nulldev-dbg
	cp bin/nulldev-dbg bin/nulldev
	strip --strip-debug --strip-unneeded bin/nulldev

flag.txt: src/flag.txt
	cp src/flag.txt flag.txt

program: bin/nulldev
	ln -fs bin/nulldev program

.PHONY: test
test: program flag.txt
	./test/test.sh

.PHONY: clean
clean:
	rm -f bin/*
	rm -f flag.txt
	unlink program || true

bin/nulldev-dbg-symbols.debug: bin/nulldev-dbg
	objcopy --only-keep-debug bin/nulldev-dbg bin/nulldev-dbg-symbols.debug

.PHONY: gdb
gdb:
	gdb -x ./.gdbinit

