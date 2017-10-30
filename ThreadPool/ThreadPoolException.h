#pragma once
#include <exception>
using namespace std;

class ThreadPoolException : public exception
{
public:
	ThreadPoolException(char*);
};