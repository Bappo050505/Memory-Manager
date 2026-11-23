#pragma once
#include "Testing.h";

int main() 
{
	Testing* tester = new Testing;
	tester->TestBase();
	tester->TestIncorrect();

	return 0;
}