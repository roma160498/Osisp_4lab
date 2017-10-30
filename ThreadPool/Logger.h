#pragma once
#include <Windows.h>
#include <process.h>
#include <string>
#include <iostream>

class Logger
{
public:
	Logger(char *);
	~Logger();
	void logInitializeThreadPool(int, int);
	void logNewTask(int);
	void logWarningAvailability();
	void logErrorExcess();
	void logErrorShortage();
	void logShutdown();
private:
	SYSTEMTIME _systemTime;
	FILE *_fileHandler;
	char *_logFileName;

	void logTime();
};