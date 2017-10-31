#pragma once
#include <Windows.h>
#include <string> // подключаем строки
#include <vector>
using namespace std;
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
