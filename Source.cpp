#include<fstream>
#include<iostream>
#include<string>
#include<queue>
#include<algorithm>
#include"memoryBlock.h"
#include"process.h"
using namespace std;

void addUniqueCriticalPoint(vector<long>&points, long val);	//add processes' arrival time
void printInputQueue(vector<process> q); //print processes to the screen

int main()
{
	int memory_size;
	int pageSize = 0;
	int numProcesses = 0;	//numbers of processes in int1.txt
	int initialNumprocesses = 0;
	fstream  file;		//reading file
	
	//Open file for reading 
	file.open("in1.txt",ios::in);
	//check if the file is opened correctly
	if (!file)
	{
		cout << "File open Error! " << endl;
		return 1;
	}
	//Add processes into FIFO queue
	queue<process>processQueue; //store processes from the input file
	vector<process>inputQueue;	//store the executed processes
	vector<long>criticalList;  //store the criticalpoints
	vector<memblock>mmu;	//
	vector<process>processesInMemory;	//processes in memory

	double totalTurnarroundTime = 0.0;

	//prompt user to input size for the memory (MMU memory size)
	cout << "Memory size >> ";
	cin >> memory_size;
	cout << endl;

//prompt user to choose the size for the page.
	do
	{
		char pageIn;
		cout << "Page Size (1: 100, 2: 200, 3: 400) >>";
		cin >> pageIn;

		switch (pageIn)
		{
		case '1':
			pageSize = 100;
			break;
		case '2':
			pageSize = 200;
			break;
		case '3':
			pageSize = 300;
			break;
		default:
			pageSize = 0;
			cout << "ERROR:  Please enter a valid value (1,2, or 3).\n";
		}

	} while (pageSize == 0);

//Initualize MMU with the size = number of possible pages in memory (memory_size/pageSize)
//initiate with 0 values
	for (int i = 0; i < (memory_size / pageSize); i++)
	{
		memblock m1;
		m1.processNum = 0;
		m1.pageNum = 0;
		mmu.push_back(m1);
	}

	file >> numProcesses;			//read processes's number in in1.txt

	cout << "Num of Processes = " << numProcesses << endl;

	initialNumprocesses = numProcesses;		//total processes in int1.txt 


//read data  processes in input file in1.txt and create the processes accordingly
	while (!file.eof() && numProcesses != 0)
	{
		int numMemoryPieces = 0; // number of repeated processes 
		process p1;
		file >> p1.processNum;	//process id#
		file >> p1.arrivalTime;
		file >> p1.burstTime;
		file >> numMemoryPieces;

 		 cout << "processNum: " << p1.processNum << "\n";
        cout << "arrivalTime: " << p1.arrivalTime << "\n";
        cout << "burstTime: " << p1.burstTime << "\n";
        cout << "memoryNeed: " << p1.memoryNeed << "\n";
	
		p1.memoryNeed = 0;
// combine all the memory needed if there more than 1 repeated processes  
		for (int i = 0; i < numMemoryPieces; i++)
		{
			int memoryPiece;
			file >> memoryPiece;
			p1.memoryNeed += memoryPiece;
			cout << "memory Need = " << p1.memoryNeed << endl;
		}
		//add all processes to FIFO queue
		processQueue.push(p1);
		
		//add arrival time to criticalpoints list if arrival time not ready in criticalpoints list
		addUniqueCriticalPoint(criticalList, p1.arrivalTime);

		numProcesses--;
	}


	//loop through the criticalpoints list and execute the processes
	while (!criticalList.empty())
	{
		bool tLine = true;	//
		bool arrivalOnly = true;
		long currentCriticalPoint = criticalList.front();	//the first process's arrival time
		cout << " t = " << currentCriticalPoint << ": ";

		
		process currentProcess = processQueue.front(); //copy the first process in the 	queue

//the the arrival time of the first process match with the time of the process in the queue
		while (currentProcess.arrivalTime == currentCriticalPoint)
		{
			processQueue.pop();
			inputQueue.push_back(currentProcess);
			
			cout << "Process " << currentProcess.processNum << " arrives" << endl;
			printInputQueue(inputQueue);  //print out executed processes's id number 
			currentProcess = processQueue.front();
		}

		criticalList.pop_back();
	}
	
	//system("pause");

	return 0;

}

//THis function add arrival time in the critical list if it is not exist the list 
void addUniqueCriticalPoint(vector<long>&points, long val)
{
	//check if the critical time is in the critical list
	vector<long>::iterator iter = find(points.begin(),points.end(),val);
	//if not in the critical list
	if (iter == points.end())
	{
		points.push_back(val);
	}
	
}

//this function print out all the the procecces's ID number   onto the screen
void printInputQueue(vector<process> q)
{
	cout << " \tInput Queue: [";
	while (!q.empty())
	{
		cout << q.front().processNum;
		q.erase(q.begin());
		if (!q.empty())
		{
			cout << " ";
		}
	}
	cout << "]" << endl;
}