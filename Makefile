all:
	gcc *.c -o build/init

run: all
	./build/init

clean:
	rm -rvf build/*
