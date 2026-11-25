#include "Testing.h"
#include <vector>


#define STARTTIMER (StartTime = std::chrono::steady_clock::now());
#define ENDTIMER (EndTime = std::chrono::steady_clock::now());
#define ELAPSEDTIME (EndTime - StartTime)


//tests if the memory manager can allocate and deallocate at the end and in the middle of the linked list.
void Testing::TestBase()
{
	LOG_FILE("\nTESTING BASIC FUNCTIONALTY\n");
	LOG_CONSOLE("TESTING BASIC FUNCTIONALTY\n");


	STARTTIMER;
	mem = new MemoryManager(512);
	void* test1 = mem->AllocateMemory(4);
	int* value1 = new(test1) int(1);
	LOG_ADDRESS_CONSOLE("\nAllocated memory at address:" , (void*)value1);
	LOG_ADDRESS_FILE("\nAllocated memory at address:", (void*)value1);
	void* test2 = mem->AllocateMemory(100);
	std::string* value2 = new(test2) std::string("Hello");
	LOG_ADDRESS_CONSOLE("\nAllocated memory at address:", test2);
	LOG_ADDRESS_FILE("\nAllocated memory at address:", test2);
	void* test3 = mem->AllocateMemory(4);
	LOG_ADDRESS_CONSOLE("\nAllocated memory at address:", test3);
	LOG_ADDRESS_FILE("\nAllocated memory at address:", test3);
	
	mem->DeallocateMemory(test2);
	LOG_ADDRESS_CONSOLE("\nDeAllocated memory at address:", test2);
	LOG_ADDRESS_FILE("\nDeAllocated memory at address:", test2);
	
	void* test4 = mem->AllocateMemory(4);
	LOG_ADDRESS_CONSOLE("\nAllocated memory at address:", test4);
	LOG_ADDRESS_FILE("\nAllocated memory at address:", test4);
	void* test5 = mem->AllocateMemory(4);
	LOG_ADDRESS_CONSOLE("\nAllocated memory at address:", test5);
	LOG_ADDRESS_FILE("\nAllocated memory at address:", test5);
	
	mem->DeallocateMemory(test1);
	LOG_ADDRESS_CONSOLE("\nDeAllocated memory at address:", test1);
	LOG_ADDRESS_FILE("\nDeAllocated memory at address:", test1);
	mem->DeallocateMemory(test3);
	LOG_ADDRESS_CONSOLE("\nDeAllocated memory at address:", test3);
	LOG_ADDRESS_FILE("\nDeAllocated memory at address:", test3);
	mem->DeallocateMemory(test4);
	LOG_ADDRESS_CONSOLE("\nDeAllocated memory at address:", test4);
	LOG_ADDRESS_FILE("\nDeAllocated memory at address:", test4);
	mem->DeallocateMemory(test5);
	LOG_ADDRESS_CONSOLE("\nDeAllocated memory at address:", test5);
	LOG_ADDRESS_FILE("\nDeAllocated memory at address:", test5);
	
	ENDTIMER;

	LOG_CONSOLE("\nTime Elapsed For basic Value Test:" + std::to_string(std::chrono::duration_cast<std::chrono::milliseconds>(EndTime - StartTime).count()) + ":milliseconds\n");
	LOG_FILE("\nTime Elapsed For basic Value Test:" + std::to_string(std::chrono::duration_cast<std::chrono::milliseconds>(EndTime - StartTime).count()) + ":milliseconds\n");
	
	delete mem;
}
//tests if the memory manager can allocate an incorrect amount of memory (e.g over max or negative values) (outputs an error if works).
void Testing::TestIncorrect()
{
	LOG_CONSOLE("\nTESTING INCORRECT VALUES\n");
	LOG_FILE("\nTESTING INCORRECT VALUES\n");
	STARTTIMER

	mem = new MemoryManager(512);

	void* test1 = mem->AllocateMemory(-1);
	LOG_CONSOLE("\nMemory allocation failed, cant allocate negative amount of memory");
	LOG_FILE("\nMemory allocation failed, cant allocate negative amount of memory");
	void* test2 = mem->AllocateMemory(1000000);
	LOG_CONSOLE("\nMemory allocation failed, out of bounds");
	LOG_FILE("\nMemory allocation failed, out of bounds");

	//tests if the memory manager can deallocate memory that dosnt exist (outputs an error if it works).
	mem->DeallocateMemory(test1);
	LOG_CONSOLE("\nCan not allocated none existant memory");
	LOG_FILE("\nCan not allocate none existant memory");
	ENDTIMER

	LOG_CONSOLE("\nTime Elapsed For incorrect Value Test:" + std::to_string(std::chrono::duration_cast<std::chrono::milliseconds>(EndTime - StartTime).count()) + ":milliseconds\n");
	LOG_FILE("\nTime Elapsed For incorrect Value Test:" + std::to_string(std::chrono::duration_cast<std::chrono::milliseconds>(EndTime - StartTime).count()) + ":milliseconds\n");
	delete mem;
}

void Testing::StressTest()
{
	LOG_CONSOLE("\nSTRESS TESTING ALLOCATE/DEALLOCATE\n");
	LOG_FILE("\nSTRESS TESTING ALLOCATE/DEALLOCATE\n");

	LOG_FILE("\nstresstesting with :" + std::to_string(stressTestAmount) + " random Allocations/Deallocations");
	LOG_CONSOLE("\nstresstesting with :" + std::to_string(stressTestAmount) + " random Allocations/Deallocations");
	STARTTIMER

	mem = new MemoryManager(100*1024*1024);
	std::vector<void*> memoryLocations;
	
	for (int i = 0; i < stressTestAmount; i++) 
	{
		int random = rand() % 2;
		
		if (random == 0 )
		{
			
			void* test = mem->AllocateMemory(1);
			memoryLocations.push_back(test);
		}
		else if(random == 1 && memoryLocations.size() > 0)
		{
			
			mem->DeallocateMemory(memoryLocations[rand()% memoryLocations.size()]);
		}
		
	
	}
	ENDTIMER
	LOG_CONSOLE("\nTime Elapsed For stress Test:" + std::to_string(std::chrono::duration_cast<std::chrono::seconds>(EndTime - StartTime).count()) + ":seconds\n");
	LOG_FILE("\nTime Elapsed For stress Test:" + std::to_string(std::chrono::duration_cast<std::chrono::seconds>(EndTime - StartTime).count()) + ":seconds\n");
		
	delete mem;
}	
void Testing::TestComplex()
{
	LOG_CONSOLE("\nCOMPLEX TYPE ALLOCATION TESTING\n");
	LOG_FILE("\nCOMPLEX TYPE ALLOCATION TESTING\n");
	STARTTIMER
	mem = new MemoryManager(2048);

	void* test1 = mem->AllocateMemory(100);
	LOG_ADDRESS_CONSOLE("\nAllocating class at memory location:", (void*)test1);
	LOG_ADDRESS_FILE("\nAllocating class at memory location:", (void*)test1);
	Dog* dog = new(test1) Dog("Barry" , "PitBull" , 4 , 10);

	mem->DeallocateMemory(test1);
	LOG_ADDRESS_CONSOLE("\nDeallocated class at memory location:", test1);
	LOG_ADDRESS_FILE("\nDeallocating class at memory location:", test1);
	
	ENDTIMER
	LOG_CONSOLE("\nTime Elapsed For Complex Value Test:" + std::to_string(std::chrono::duration_cast<std::chrono::milliseconds>(EndTime - StartTime).count()) + ":milliseconds\n");
	LOG_FILE("\nTime Elapsed For Complex Value Test:" + std::to_string(std::chrono::duration_cast<std::chrono::milliseconds>(EndTime - StartTime).count()) + ":milliseconds\n");

	delete mem;
	

}
;



