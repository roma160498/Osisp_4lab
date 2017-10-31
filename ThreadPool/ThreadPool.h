#pragma once
#include <Windows.h>
#include "Thread.h"
#include "TaskQueue.h"

class ThreadPool
{
public:
	ThreadPool(int, TaskQueue * tasks);
	~ThreadPool();
	void run();
	void wait();
private:
	Thread *repositoryOfThreads;
	TaskQueue *taskQueue;
	int numberOfThreads;

	int getNumberOfFreeThread();
	bool isAvailabilityThread(Thread *);
	bool isStillActive(Thread*, DWORD);
};
