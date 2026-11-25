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
	void* test2 = mem->AllocateMemory(100);
	std::string* value2 = new(test2) std::string("Hello");
	void* test3 = mem->AllocateMemory(4);
	
	mem->DeallocateMemory(test2);
	
	void* test4 = mem->AllocateMemory(4);
	void* test5 = mem->AllocateMemory(4);
	
	mem->DeallocateMemory(test1);
	mem->DeallocateMemory(test3);
	mem->DeallocateMemory(test4);
	mem->DeallocateMemory(test5);
	
	ENDTIMER;

	LOG_CONSOLE("Time Elapsed For basic Value Test:" + std::to_string(std::chrono::duration_cast<std::chrono::nanoseconds>(EndTime - StartTime).count()) + "\n");
	LOG_FILE("Time Elapsed For basic Value Test:" + std::to_string(std::chrono::duration_cast<std::chrono::nanoseconds>(EndTime - StartTime).count()) + "\n");
	
	delete mem;
}
//tests if the memory manager can allocate an incorrect amount of memory (e.g over max or negative values) (outputs an error if works).
void Testing::TestIncorrect()
{
	STARTTIMER
	LOG_CONSOLE("\nTESTING INCORRECT VALUES\n");
	LOG_FILE("\nTESTING INCORRECT VALUES\n");

	mem = new MemoryManager(512);

	void* test1 = mem->AllocateMemory(-1);
	void* test2 = mem->AllocateMemory(1000000);

	//tests if the memory manager can deallocate memory that dosnt exist (outputs an error if it works).
	mem->DeallocateMemory(test1);
	ENDTIMER

	LOG_CONSOLE("Time Elapsed For incorrect Value Test:" + std::to_string(std::chrono::duration_cast<std::chrono::nanoseconds>(EndTime - StartTime).count()) + "\n");
	LOG_FILE("Time Elapsed For incorrect Value Test:" + std::to_string(std::chrono::duration_cast<std::chrono::nanoseconds>(EndTime - StartTime).count()) + "\n");
	delete mem;
}

void Testing::StressTest()
{
	STARTTIMER
	LOG_CONSOLE("\nSTRESS TESTING ALLOCATE/DEALLOCATE\n");
	LOG_FILE("\nSTRESS TESTING ALLOCATE/DEALLOCATE\n");

	mem = new MemoryManager(1*1024*1024);
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
	LOG_CONSOLE("Time Elapsed For stress Test:" + std::to_string(std::chrono::duration_cast<std::chrono::nanoseconds>(EndTime - StartTime).count()) + "\n");
	LOG_FILE("Time Elapsed For stress Test:" + std::to_string(std::chrono::duration_cast<std::chrono::nanoseconds>(EndTime - StartTime).count()) + "\n");
		
	delete mem;
}	
void Testing::TestComplex()
{
	LOG_CONSOLE("\nCOMPLEX TYPE ALLOCATION TESTING\n");
	LOG_FILE("\nCOMPLEX TYPE ALLOCATION TESTING\n");
	STARTTIMER
	mem = new MemoryManager(2048);

	void* test1 = mem->AllocateMemory(100);
	Dog* dog = new(test1) Dog("Barry" , "PitBull" , 4 , 10);

	mem->DeallocateMemory(test1);
	
	ENDTIMER
	LOG_CONSOLE("Time Elapsed For Complex Value Test:" + std::to_string(std::chrono::duration_cast<std::chrono::nanoseconds>(EndTime - StartTime).count()) + "\n");
	LOG_FILE("Time Elapsed For Complex Value Test:" + std::to_string(std::chrono::duration_cast<std::chrono::nanoseconds>(EndTime - StartTime).count()) + "\n");

	delete mem;
	

}
;



