#pragma once
#include <Windows.h>
#include "ThreadPoolException.h"
#include "Logger.h"
#include <string> // подключаем строки
#include <vector>

class Thread
{
public:
	Thread();
	~Thread();
	HANDLE getHThread();
	void createNewThread(LPTHREAD_START_ROUTINE, vector<string> *);
private:
	HANDLE _hThread;
};
