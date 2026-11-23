#pragma once
#include <iostream>
#include <chrono>
#include "MemoryManager.h"

class Testing
{
private:
	std::chrono::time_point<std::chrono::steady_clock> StartTime;
	std::chrono::time_point<std::chrono::steady_clock> EndTime;
	MemoryManager* mem;
	const int stressTestAmount = 10000000;
public:
	void TestBase();
	void TestIncorrect();
	void StressTest();
	void TestComplex();

};



