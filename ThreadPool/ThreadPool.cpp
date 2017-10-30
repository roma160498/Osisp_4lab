#include "stdafx.h"
#include "ThreadPool.h"

ThreadPool::ThreadPool(int numberOfThreads,TaskQueue * tasks)
{
	_repositoryThreads = new Thread[numberOfThreads];
	taskQueue = tasks;
	_numberOfThreads = numberOfThreads;
	_logger = new Logger("logfile.dat");
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

	TerminateThread(thread->getHThread(), 0);
	return false;
}

int ThreadPool::getNumberOfFreeThread()
{
	for (int i = 0; i < _numberOfThreads; i++)
	{
		if (isAvailabilityThread(&_repositoryThreads[i]))
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
			_repositoryThreads[currentThreadNumber].createNewThread((LPTHREAD_START_ROUTINE)(task->threadFunction), task->pParam);
		}
	} while (taskQueue->elemLeft() != 0);
}

ThreadPool::~ThreadPool()
{
	_logger->logShutdown();
	_logger->~Logger();
}

void ThreadPool::wait()
{
	while (taskQueue->elemLeft() != 0)
		Sleep(100);
	Sleep(1000);
	taskQueue->resetIndex();
}