#include<fstream>
#include<iostream>
#include<string>
#include<queue>
#include<algorithm>
#include"memblock.h"
#include"process.h"
using namespace std;

void addUniqueCriticalPoint(vector<long>&points, long val);
void printInputQueue(vector<process> q);

int main()
{
	int memory_size;
	int pageSize = 0;
	int numProcesses = 0;
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
	queue<process>processQueue;
	vector<process>inputQueue;
	vector<long>criticalList;  //store the criticalpoints
	vector<memblock>mmu;
	vector<process>processesInMemory;

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

//Initualize MMU with value: 0
	for (int i = 0; i < (memory_size / pageSize); i++)
	{
		memblock m1;
		m1.processNum = 0;
		m1.pageNum = 0;
		mmu.push_back(m1);
	}

	file >> numProcesses;			//read number of processes in in1.txt

	cout << "Num of Processes = " << numProcesses << endl;

	initialNumprocesses = numProcesses;

	while (!file.eof() && numProcesses != 0)
	{
		int numMemoryPieces = 0;
		process p1;
		file >> p1.processNum;
		cout << "Process number: " << p1.processNum << endl;
		file >> p1.arrivalTime;
		cout << "Process arrivial time: " << p1.arrivalTime << endl;
		file >> p1.burstTime;
		cout << "Process burt-time: " << p1.burstTime << endl;
		file >> numMemoryPieces;
	
		cout << "Num memoryPieces = " << numMemoryPieces << endl;	
		p1.memoryNeed = 0;

		for (int i = 0; i < numMemoryPieces; i++)
		{
			int memoryPiece;
			file >> memoryPiece;
			p1.memoryNeed += memoryPiece;
			cout << "memory Need = " << p1.memoryNeed << endl;
		}
		
		processQueue.push(p1);
		//add arrival time to criticalpoints list if arrival time not ready in criticalpoints list
		addUniqueCriticalPoint(criticalList, p1.arrivalTime);

		numProcesses--;
	}

	//loop through the criticalpoints list
	while (!criticalList.empty())
	{
		bool tLine = true;
		bool arrivalOnly = true;
		long currentCriticalPoint = criticalList.front();
		cout << " t = " << currentCriticalPoint << ": ";

		//move process from processQueue to inputQueue if criticalPoint matches arrival time, else it must be a completion time 
		process currentProcess = processQueue.front();
		while (currentProcess.arrivalTime == currentCriticalPoint)
		{
			processQueue.pop();
			inputQueue.push_back(currentProcess);
			if (tLine)
			{
				tLine = false;
			}
			else {
				cout << "\t";
			}
			cout << "Process " << currentProcess.processNum << " arrives" << endl;
			printInputQueue(inputQueue);


		}

	}
	system("pause");
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