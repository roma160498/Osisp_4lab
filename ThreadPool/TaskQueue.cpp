#include "stdafx.h"

#include "TaskQueue.h"

TaskQueue::TaskQueue()
{
	tasksCount = 0;
	taskIndex = 0;
	taskCS = (CRITICAL_SECTION*)malloc(sizeof(CRITICAL_SECTION));
	InitializeCriticalSection(taskCS);
}
long TaskQueue::elemLeft()
{
	return taskIndex;
}

void TaskQueue::addNewTask(Task * task)
{
	EnterCriticalSection(taskCS);
	InterlockedIncrement(&tasksCount);
	InterlockedIncrement(&taskIndex);
	if (tasks == NULL) {
		tasks = (Task*)malloc(sizeof(Task)*tasksCount);
	}
	else {
		tasks = (Task*)realloc(tasks, sizeof(Task)*tasksCount);
	}
	tasks[tasksCount - 1] = *task;
	LeaveCriticalSection(taskCS);
}
void TaskQueue::resetIndex()
{
	InterlockedExchange(&taskIndex, tasksCount);
}
Task * TaskQueue::takeTask()
{
	EnterCriticalSection(taskCS);
	Task * tempTask;
	
	tempTask = &tasks[taskIndex - 1];
	InterlockedDecrement(&taskIndex);
	//tasks = (Task*)realloc(tasks, sizeof(Task)*tasksCount);
	LeaveCriticalSection(taskCS);
	return tempTask;
}