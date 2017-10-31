#pragma once
#include <Windows.h>
#include <string> // подключаем строки
#include <vector>
using namespace std;
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
	CRITICAL_SECTION taskCS;
	volatile long taskIndex;
};
