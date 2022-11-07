PROGNAME=stackframe_massacre_2

.PHONY: all
all: program flag.txt bin/$(PROGNAME)-dbg-symbols.debug

bin:
	mkdir -p bin

bin/$(PROGNAME)-dbg: src/$(PROGNAME).c bin
	clang -z execstack src/$(PROGNAME).c -o bin/$(PROGNAME)-dbg -g3 -O0 -static

bin/$(PROGNAME): bin/$(PROGNAME)-dbg
	cp bin/$(PROGNAME)-dbg bin/$(PROGNAME)
	strip --strip-debug --strip-unneeded bin/$(PROGNAME)

flag.txt: src/flag.txt
	cp src/flag.txt flag.txt

program: bin/$(PROGNAME)
	ln -fs bin/$(PROGNAME) program

.PHONY: test
test: program flag.txt
	./test/test.sh

.PHONY: clean
clean:
	rm -f bin/*
	rm -f flag.txt
	unlink program || true

bin/$(PROGNAME)-dbg-symbols.debug: bin/$(PROGNAME)-dbg
	objcopy --only-keep-debug bin/$(PROGNAME)-dbg bin/$(PROGNAME)-dbg-symbols.debug

.PHONY: gdb
gdb:
	gdb -x ./.gdbinit
