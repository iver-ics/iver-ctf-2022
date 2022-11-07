all:
	mkdir -p bin
	cd bin;(head /dev/urandom -c 24122 ; cat ../src/flag.txt ; head /dev/urandom -c 15234) >file
	cd bin;python3 ../src/transform.py
