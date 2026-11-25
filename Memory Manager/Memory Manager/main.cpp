#pragma once
#include "Testing.h";

int main() 
{
	srand(4);
	Testing* tester = new Testing;
	tester->TestBase();
	tester->TestIncorrect();
	tester->TestComplex();
	tester->StressTest();
	return 0;
}