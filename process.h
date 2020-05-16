#include <iostream>

#pragma once

struct process
{
	int processNum; 	//process number
	int arrivalTime;	//time submitted to system
	//int endTime;		//time process ends
	int lifeTime;		//lifetime after admitted to memory
	int memoryNeed = 0;		//memory requirements

	int numMem = 0; 		//number of times to add to memory needed

	friend std::istream& operator >> (std::istream& is, process& p) {
		is >> p.processNum >> p.arrivalTime >> p.lifeTime >> p.numMem;
		for (size_t i = 0; i < p.numMem; i++)
		{
			int temp = 0;
			is >> temp;
			p.memoryNeed += temp;
		}
		return is;
	}

	friend std::ostream& operator << (std::ostream& os, process& p) {
		os << "Process Number: " << p.processNum << "\n";
        os << "\tArrival Time: " << p.arrivalTime << "\n";
        os << "\tLife Time: " << p.lifeTime << "\n";
		os << "\tMemory Need = " << p.memoryNeed << "\n";
		return os;
	}
};

