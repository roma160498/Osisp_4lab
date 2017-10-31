#include "stdafx.h"
#include "ThreadPool.h"

ThreadPool::ThreadPool(int amount,TaskQueue * tasks)
{
	repositoryOfThreads = new Thread[amount];
	taskQueue = tasks;
	numberOfThreads = amount;
}

bool ThreadPool::isAvailabilityThread(Thread *thread)
{
	DWORD status;
	GetExitCodeThread(thread->getHThread(), &status);
	return !isStillActive(thread, status);
}

bool ThreadPool::isStillActive(Thread *thread, DWORD status)
{
	if (status == STILL_ACTIVE)
		return true;

	//TerminateThread(thread->getHThread(), 0);
	return false;
}

int ThreadPool::getNumberOfFreeThread()
{
	for (int i = 0; i < numberOfThreads; i++)
	{
		if (isAvailabilityThread(&repositoryOfThreads[i]))
			return i;
	}
	return -1;
}

void ThreadPool::run()
{
	do {
		int currentThreadNumber = getNumberOfFreeThread();
		if (currentThreadNumber != -1)
		{
			Task * task = taskQueue->takeTask();
			repositoryOfThreads[currentThreadNumber].createNewThread((LPTHREAD_START_ROUTINE)(task->threadFunction), task->pParam);
		}
	} while (taskQueue->elemLeft() != 0);
}

ThreadPool::~ThreadPool()
{
/*	for (int i = 0; i < numberOfThreads; i++) {
		delete &repositoryOfThreads[i];
	}*/
	//DeleteCriticalSection(resultCS);
	//DeleteCriticalSection(taskCS);
}

void ThreadPool::wait()
{
	while (taskQueue->elemLeft() != 0)
		Sleep(100);
	Sleep(1000);
	taskQueue->resetIndex();
}