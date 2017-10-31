#include "stdafx.h"
#include "ThreadPool.h"
#include "TaskQueue.h"
#include <conio.h> 
#include <fstream> 
#include <algorithm>
#include <iostream>
#include <vector>
#include <map>

using namespace std;

int lineCount = 0, amountOfParts = 0;

int countLines(string fileName)
{
	string line;
	ifstream file(fileName);
	int tempCounter = 0;
	if (!file) {
		cout << "Error with opening file";
		return -1;
	}
	while (getline(file, line)) {
		tempCounter++;
	}
	file.close();
	return tempCounter;
}

void sortFilePart(vector<string> * lines)
{
	sort((*lines).begin(), (*lines).end());
}

void resultSort(int l, int r, vector<string> * linesmap,int size) {
	if (r == l)
		return;
	if (r - l == 1) {
		if ((*linesmap)[r] < (*linesmap)[l])
			swap((*linesmap)[r], (*linesmap)[l]);
		return;
	}
	int m = (r + l) / 2;
	resultSort(l, m, linesmap, size);
	resultSort(m + 1, r,linesmap, size);
	vector<string> buf(size);
	int xl = l;
	int xr = m + 1;
	int cur = 0;
	while (r - l + 1 != cur) {
		if (xl > m)
			buf[cur++] = (*linesmap)[xr++];
		else if (xr > r)
			buf[cur++] = (*linesmap)[xl++];
		else if ((*linesmap)[xl] > (*linesmap)[xr])
			buf[cur++] = (*linesmap)[xr++];
		else buf[cur++] = (*linesmap)[xl++];

	}
	for (int i = 0; i < cur; i++)
		(*linesmap)[i + l] = buf[i];
}

int main()
{
	string line;
	TaskQueue *taskQueue = new TaskQueue();
	ThreadPool *threadPool;	
	int  linesInOnePart = 0, tempCounter = 0,i;

	cout << "Input amount of parts: ";
	cin >> amountOfParts;
	std::vector<std::vector<string>> lines(amountOfParts);
	Task* task = (Task*)malloc(sizeof(Task)*amountOfParts);

	lineCount = countLines("1.txt");
	if (lineCount == -1)
		return -1;

	linesInOnePart = lineCount / amountOfParts +1;

	ifstream file;
	file.open("1.txt");
	for ( i = 0;  i < amountOfParts-1; i++)
	{
		while (tempCounter!=(i+1)*linesInOnePart) {
			if (getline(file, line))
			{
				tempCounter++;
				lines[i].push_back(line);
			}
		}
		task[i].pParam = &lines[i];
		task[i].threadFunction = &sortFilePart;
		taskQueue->addNewTask(task+i);
	}
	while (getline(file, line)) {
		tempCounter++;
		lines[i].push_back(line);
	}
	task[i].pParam = &lines[i];
	task[i].threadFunction = &sortFilePart;
	taskQueue->addNewTask(task+i);
	file.close(); 

	threadPool = new ThreadPool(amountOfParts, taskQueue);
	threadPool->run();
	threadPool->wait();
	threadPool->~ThreadPool();

	vector<string> partHeads;

	//1 realization
	for (int i = 0; i < amountOfParts; i++)
	{
		Task * task = taskQueue->takeTask();
		vector<string> * vect = task->pParam;
		for (int j = 0; j < (*vect).size(); j++)
			partHeads.push_back((*vect)[j]);
	}

	resultSort(0, lineCount - 1, &partHeads,lineCount);

	ofstream fout("reslut.txt");
	for (int i = 0; i < lineCount; i++)
	{
		fout << partHeads[i] << "\n";
	}
	fout.close(); 

	//2 realization
	/*for (int i = 0; i < amountOfParts; i++)
	{
		Task * task = taskQueue->takeTask();
		vector<string> * vect = task->pParam;
		partHeads.push_back((*vect)[0]);
	}

	resultSort(0, amountOfParts - 1,&partHeads,amountOfParts);

	ofstream fout("reslut.txt");
	for (int i = 0; i < amountOfParts; i++)
	{
		for (int j = 0; j < amountOfParts; j++)
			if (partHeads[i] == lines[j][0])
			{
				for (int k = 0; k < lines[j].size(); k++)
					fout << lines[j][k] << "\n";
				fout << "\n";
			}
	}
	fout.close(); */
	taskQueue->~TaskQueue();
	cout << "Completed!";
	_getch();
	return 0;
}

