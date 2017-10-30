#pragma once
#include <Windows.h>
#include "ThreadPoolException.h"
#include "Logger.h"
#include <string> // подключаем строки
#include <vector>

struct Task
{
	vector<string> * pParam;
	void (*threadFunction)(vector<string> *);
};

class TaskQueue
{
public:
	TaskQueue();
	~TaskQueue();
	void addNewTask(Task *);
	Task * takeTask();
	void resetIndex();
	long elemLeft();
private:
	Task *tasks = NULL;
	volatile long tasksCount;
	CRITICAL_SECTION* taskCS;
	volatile long taskIndex;

	int getNumberOfFreeThread();
	//bool isAvailabilityThread(Thread *);
	//bool isStillActive(Thread*, DWORD);
	void initialization(int, int);
	void initializationOfPool(int, int);
	void setMaxNumberOfThreads(int);

	Logger *_logger;
};
