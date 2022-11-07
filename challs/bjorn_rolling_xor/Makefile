all:
	mkdir -p bin
	gcc src/generate.c -o bin/generate
	cd bin ; (cat ../src/flag.txt | ./generate)
	cd bin && ((xxd --include randoms.bin;xxd --include result.bin;cat ../src/template.c)>program.c) && \
	 gcc program.c -o program