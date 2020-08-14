all:
	mkdir build
	gcc *.c -o build/init

clean:
	rm -rvf build
