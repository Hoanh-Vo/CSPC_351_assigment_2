# ./output to run the program



output: Source.o
	g++ Source.o -o output

Source.o: Source.cpp process.h memoryBlock.h
	g++ -c Source.cpp

clean:
	rm *.o output
