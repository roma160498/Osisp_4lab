#include "stdafx.h"
#include "ThreadPool.h"
#include "TaskQueue.h"
#include <conio.h> 
#include <string> // подключаем строки
#include <fstream> // подключаем файлы
#include <vector>
#include <algorithm>

void testMethod2()
{
	Sleep(3000);
	printf("Method 2 done\n");
}

void testMethod()
{
	Sleep(4000);
	printf("Method done\n");
}

void sortFilePart(vector<string> * lines)
{
	sort((*lines).begin(), (*lines).end());
}

int main()
{
	string s;
	TaskQueue *taskQueue = new TaskQueue();
	ThreadPool *threadPool;
	int amountOfParts;
	std::vector<std::vector<string>> lines(3);



	int lineCount=0;
	int linesInPart = 0;
	int tempCounter = 0;
	cout << "Input amount of parts: ";
	cin >> amountOfParts;
	
	Task* task = (Task*)malloc(sizeof(Task)*amountOfParts);
	ifstream file("1.txt"); 
	while (getline(file, s)) { 
		lineCount++;
	}
	file.close();
	linesInPart = lineCount / amountOfParts +1;
	ifstream file2("1.txt");
	int i = 0;
	for ( i = 0;  i < amountOfParts-1; i++)
	{
		while (tempCounter!=(i+1)*linesInPart) {
			if (getline(file2, s))
			{
				tempCounter++;
				lines[i].push_back(s);
			}
		}
		task[i].pParam = &lines[i];
		task[i].threadFunction = &sortFilePart;
		taskQueue->addNewTask(task+i);
		//lines.clear();
	}

	while (getline(file2, s)) {
		tempCounter++;
		lines[i].push_back(s);
	}
	task[i].pParam = &lines[i];
	task[i].threadFunction = &sortFilePart;
	taskQueue->addNewTask(task+i);

	file2.close(); 


	try
	{
		threadPool = new ThreadPool(amountOfParts, taskQueue);
		threadPool->run();
		threadPool->~ThreadPool();
	}
	catch (const ThreadPoolException& e)
	{
		printf(e.what());
	}

	threadPool->wait();

	ofstream fout("cppstudio.txt"); // создаём объект класса ofstream для записи и связываем его с файлом cppstudio.txt
	for (int i = 0; i < amountOfParts; i++)
	{
		Task * task = taskQueue->takeTask();
		vector<string> * vect = task->pParam;
		for (int j=0; j<vect->size();j++)
			fout << (*vect)[j]<<"\n";
	}

	fout.close(); // закрываем файл

	
	_getch();
	return 0;
}