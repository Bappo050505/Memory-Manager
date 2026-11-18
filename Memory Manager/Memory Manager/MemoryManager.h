#pragma once
#include <iostream>

typedef char byte;
class MemoryManager
{

private:
	
	struct MetaData 
	{
		byte* location;
		MetaData* next;
		size_t size;
	};

	MetaData* head = nullptr;
	MetaData* tail = nullptr;

	void* address;
public:
	MemoryManager(size_t s);
	~MemoryManager();

	void* AllocateMemory(size_t size);
	void DeallocateMemory(void* del);
	void Output();
};

