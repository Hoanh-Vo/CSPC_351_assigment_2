

output: source.o
	g++ source.o -o output

source.o: source.cpp process.h memblock.h
	g++ -c source.cpp

clean:
	rm *.o output
