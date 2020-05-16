#include<fstream>
#include<iostream>
#include<queue>
#include<algorithm>
#include"memoryBlock.h"
#include"process.h"

void addCriticalPoint(std::vector<long>& critList, long time);	//Add processes' arrival time
void printInputQueue(std::vector<process> q); //Print processes to the screen
void getUserInput(int &ms, int &ps); //Gets user input

int main()
{
	int memory_size;
	int pageSize = 0;
	int numProcesses = 0;							//Numbers of processes in int1.txt
	//double totalTurnarroundTime = 0.0;
	std::fstream  file;								//Reading file

	//Add processes into FIFO queue
	std::queue<process>processQueue; 				//Store processes from the input file
	std::vector<process>inputQueue;	 				//Store the executed processes
	std::vector<long>criticalList;   				//Store the criticalpoints
	std::vector<memblock>mmu;	
	std::vector<process>processesInMemory;			//Processes in memory

	getUserInput(memory_size, pageSize);

	//Initualize MMU with the size = number of possible pages in memory (memory_size/pageSize)
	//Initiatize with 0 values
	for (int i = 0; i < (memory_size / pageSize); i++)
	{
		memblock m;
		m.processNum = 0;
		m.pageNum = 0;
		mmu.push_back(m);
	}
	
	//Open file for reading 
	file.open("in1.txt",std::ios::in);

	//Check if the file is opened correctly
	if (!file.is_open())
	{
		std::cout << "File open Error! \n";
		return 1;
	}

	file >> numProcesses;							//Read processes's number in in1.txt
	std::cout << "Num of Processes = " << numProcesses << "\n";

	//Read data  processes in input file in1.txt and create the processes accordingly
	while (!file.eof() && numProcesses != 0)
	{
		process p;
		file >> p;
		std::cout << p;
		
		//Add all processes to FIFO queue
		processQueue.push(p);
		
		//Add arrival time to criticalpoints list if arrival time not ready in criticalpoints list
		addCriticalPoint(criticalList, p.arrivalTime);

		--numProcesses;
	}

	//Loop through the criticalpoints list and execute the processes
	while (!criticalList.empty())
	{
		//bool tLine = true;	
		//bool arrivalOnly = true;
		long currentCriticalPoint = criticalList.front();		//The first process's arrival time
		std::cout << " t = " << currentCriticalPoint << ": ";

		
		process currentProcess = processQueue.front(); 			//The first process in the queue

		//The the arrival time of the first process match with the time of the process in the queue
		while (currentProcess.arrivalTime == currentCriticalPoint)
		{
			processQueue.pop();
			inputQueue.push_back(currentProcess);
			
			std::cout << "Process " << currentProcess.processNum << " arrives\n";
			printInputQueue(inputQueue);  						//Print out executed processes's id number 
			currentProcess = processQueue.front();
		}

		//Loop through MMU 
		for(auto i = processesInMemory.begin(); i != processesInMemory.end();i++)
		{
			currentProcess = *i;
		}
		criticalList.pop_back();
	}
	
	std::cout << "\n";

	return 0;

}

//This function add arrival time in the critical list if it is not exist the list 
void addCriticalPoint(std::vector<long>& critList, long time)
{
	//Check if the critical time is in the critical list
	std::vector<long>::iterator iter = find(critList.begin(),critList.end(),time);
	//If not in the critical list
	if (iter == critList.end())
	{
		critList.push_back(time);
	}
	
}

//This function print out all the the procecces's ID number onto the screen
void printInputQueue(std::vector<process> q)
{
	std::cout << " \tInput Queue: [";
	while (!q.empty())
	{
		std::cout << q.front().processNum;
		q.erase(q.begin());
		if (!q.empty())
		{
			std::cout << " ";
		}
	}
	std::cout << "]\n";
}

//This function gets the user input for memory size and page size
void getUserInput(int &ms, int &ps) {
	//Prompt user to input size for the memory (MMU memory size)
	std::cout << "Memory size >> ";
	std::cin >> ms;
	std::cout << "\n";

	//Prompt user to choose the size for the page.
	do
	{
		int pageInput;
		std::cout << "Page Size (1: 100, 2: 200, 3: 400) >> ";
		std::cin >> pageInput;

		switch (pageInput)
		{
		case 1:
			ps = 100;
			break;
		case 2:
			ps = 200;
			break;
		case 3:
			ps = 300;
			break;
		default:
			ps = 0;
			std::cout << "ERROR:  Please enter a valid value (1,2, or 3).\n";
		}
	} while (ps == 0);
}
