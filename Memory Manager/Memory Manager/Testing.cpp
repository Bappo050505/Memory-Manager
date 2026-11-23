#include "Testing.h"


#define STARTTIMER (StartTime = std::chrono::steady_clock::now());
#define ENDTIMER (EndTime = std::chrono::steady_clock::now());

//tests if the memory manager can allocate and deallocate at the end and in the middle of the linked list.
void Testing::TestBase()
{
	std::cout << "\nTESTING BASIC FUNCTIONALTY\n";

	STARTTIMER
	mem = new MemoryManager(512);
	
	void* test1 = mem->AllocateMemory(4);
	int* value1 = new(test1) int(1);
	void* test2 = mem->AllocateMemory(100);
	std::string* value2 = new(test2) std::string("Hello");
	std::cout << *value2;
	void* test3 = mem->AllocateMemory(4);
	
	mem->Output();
	
	mem->DeallocateMemory(test2);
	
	mem->Output();
	

	void* test4 = mem->AllocateMemory(4);
	void* test5 = mem->AllocateMemory(4);
	
	mem->Output();

	mem->DeallocateMemory(test1);
	mem->DeallocateMemory(test3);
	mem->DeallocateMemory(test4);
	mem->DeallocateMemory(test5);
	std::cout << "\n";
	ENDTIMER

	std::cout << "Time Elapsed For Base Test:"<< (EndTime - StartTime) << "\n";
	
	delete mem;
}
//tests if the memory manager can allocate an incorrect amount of memory (e.g over max or negative values) (outputs an error if works).
void Testing::TestIncorrect()
{
	STARTTIMER
	std::cout << "\nTESTING INCORRECT VALUES\n";

	mem = new MemoryManager(512);

	void* test1 = mem->AllocateMemory(-1);
	void* test2 = mem->AllocateMemory(1000000);
	
	mem->Output();

	//tests if the memory manager can deallocate memory that dosnt exist (outputs an error if it works).
	mem->DeallocateMemory(test1);
	ENDTIMER
	std::cout << "Time Elapsed For Incorrect Value Test:" << (EndTime - StartTime) << "\n";
	delete mem;
}

void Testing::StressTest()
{
	std::cout << "\n STRESS TESTING ALLOCATE/DEALLOCATE\n";

	for (int i = 0; i < stressTestAmount; i++) 
	{
		//structure for stress test;
		//rand between 0 and 1 , if 0 allocate , if 1 deallocate
		//note : need to keep track of allocated values for deallocation later.
	}

}
void Testing::TestComplex()
{
}
;



