#include "MemoryManager.h"

MemoryManager::MemoryManager(size_t size)
{
	address = operator new(size);
}

MemoryManager::~MemoryManager()
{
	if (address != nullptr) 
	{
		operator delete(address);
		address = nullptr;
	}
}


void* MemoryManager::AllocateMemory(size_t size)
{
    //makes the data packet
    MetaData* data = new MetaData;


    if (head == nullptr)
    {
        //populate the first data packet
        data->location = (byte*)address;
        data->size = size;
        data->next = nullptr;

        head = data;
        //returns if the head exists
        return data->location;
    }
    //temp packet that saves others
    MetaData* temp = head;

    //cycles to the end of the list
    while (temp->next != nullptr)
    {
        temp = temp->next;
    }
    //allows to set new packet at the end of linked list
    data->location = temp->location + temp->size;
    data->size = size;
    data->next = nullptr;
    //sets next data 
    temp->next = data;

   //output (always last thing to do)
    temp = head;
    while (temp != nullptr)
    {
        std::cout << (void*)temp->location << "\n";
        temp = temp->next;
    }
    std::cout << "\n\n\n";

    return data->location;
}


void MemoryManager::DeallocateMemory()
{

}
