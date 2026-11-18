#pragma once
#include "MemoryManager.h"
MemoryManager* mem;
int main() 
{
	mem = new MemoryManager(512);

	void* test1 = mem->AllocateMemory(1);
	void* test2 = mem->AllocateMemory(100);
	void* test3 = mem->AllocateMemory(1);
	
	mem->DeallocateMemory(test2);

	mem->Output();

	void* test4 = mem->AllocateMemory(4);
	void* test5 = mem->AllocateMemory(4);

	mem->Output();
	
	return 0;
}