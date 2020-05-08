# 

output: Source.o
	g++ Source.o -o output

Source.o: Source.cpp process.h memblock.h
	g++ -c Source.cpp

clean:
	rm *.o output
