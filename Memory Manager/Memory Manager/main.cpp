#pragma once
#include "MemoryManager.h"
MemoryManager* mem;
int main() 
{
	mem = new MemoryManager(64);

	mem->AllocateMemory(1);
	mem->AllocateMemory(2);
	mem->AllocateMemory(3);
	mem->AllocateMemory(4);
	mem->AllocateMemory(5);

	return 0;
}