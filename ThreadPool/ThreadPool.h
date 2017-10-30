#pragma once
#include <Windows.h>
#include "Thread.h"
#include "TaskQueue.h"
#include "ThreadPoolException.h"
#include "Logger.h"

class ThreadPool
{
public:
	ThreadPool(int, int);
	ThreadPool(int, TaskQueue * tasks);
	~ThreadPool();
	void run();
	void wait();
	void addNewTask(LPTHREAD_START_ROUTINE);
	void addNewThreadInPool();
	void deleteThreadInPool();
private:
	Thread *_repositoryThreads;
	TaskQueue *taskQueue;
	int _numberOfThreads;
	int _maxNumberOfThreads;
	const int DEFAULT_NUMBER_THREADS = 2;

	int getNumberOfFreeThread();
	bool isAvailabilityThread(Thread *);
	bool isStillActive(Thread*, DWORD);
	void initialization(int, int);
	void initializationOfPool(int, int);
	void setMaxNumberOfThreads(int);

	Logger *_logger;
};
