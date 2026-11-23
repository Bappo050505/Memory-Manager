#include "MemoryManager.h"

MemoryManager::MemoryManager(size_t size)
{
	address = malloc(size);
    MemoryRem = size;
    MetaDataSize = sizeof(MetaData);
}

MemoryManager::~MemoryManager()
{
	if (address != nullptr) 
	{
		free(address);
		address = nullptr;
	}
}

void* MemoryManager::AllocateMemory(size_t size)
{
    if (!((int)size > 0)) 
    {
        std::cout << "ERROR:can not allocate a negative value or zero to memory\n";
        return 0;
    }
    if (size > MemoryRem)
    {
        std::cout << "ERROR:not enought memory to allocate to\n";
        return 0;
    }

    if (head == nullptr)
    {
        //makes head packet
        MetaData* data = (MetaData*)(address);
        //populate the first data packet
        data->location = (byte*)address + MetaDataSize;
        data->size = size + MetaDataSize;
        data->next = nullptr;

        head = data;
        MemoryRem - data->size;
        //returns if the head exists
        return data->location;
    }
    //temp packet that saves others
    MetaData* temp = head;


    //cycles to the end of the list
    while (temp->next != nullptr)
    {
        //checks if there is space between 2 packets
        if (temp->next != nullptr)
        {
            size_t spaceleft = ((size_t)(temp->next->location) - (size_t)(temp->location + temp->size));
            if (spaceleft > 0) 
            {
                //checks if the new packet will fit in said space
                if (size < spaceleft) 
                {
                    //slot the new packet into the space
                    std::cout<< "spaceleft:" << spaceleft << "\n";       
                    MetaData* data = (MetaData*)(temp + temp->size);
                    data->location = temp->location + temp->size;
                    data->size = size + MetaDataSize;
                    data->next = temp->next;
                    temp->next = data;
                    MemoryRem = MemoryRem - data->size;
             
                    return data->location;
                }
            
            }
        }
        temp = temp->next;
    }

    //allows to set new packet at the end of linked list

    MetaData* data = (MetaData*)(temp->location + temp->size - MetaDataSize);

    //std::cout << "size+loc:" << (int)(temp->location + temp->size);
    data->location = temp->location + temp->size;
    data->size = size + MetaDataSize;
    data->next = nullptr;
    //sets next data 
    temp->next = data;
    MemoryRem = MemoryRem - data->size;



    return data->location;
}


void MemoryManager::DeallocateMemory(void* del)
{
    //grabs head
    MetaData* temp = head;
    //deallocate if mem is in head
    if (del != nullptr)
    {
        if (head->location == del) 
        {
            //cache head
            MetaData* todel = head;
            std::cout << "DEALLOCATING MEMORY AT LOCATION:" << (void*)temp->location << "\n";
            //set head to next value
            head = temp->next;
            //delete cached head
           
        }
        else
        {
            //checks if value to deallocate has been reached
            while (temp->next != nullptr)
            {
                if (temp->next->location != del)
                {
                    //sets temp to the next value
                    temp = temp->next;
                    continue;
                }
                //caches the value to deallocate
                MetaData* todel = temp->next;
                MemoryRem = MemoryRem + temp->next->size;
                //relinks the list
                temp->next = temp->next->next;

               

              
                return;
            }        
                 
        }
    }
    else 
    {
        std::cout << "nothing to deallocate\n";
    }
}

void MemoryManager::Output()
{
    //output (always last thing to do)
    MetaData* temp = head;

    if (head == nullptr)
    {
        std::cout << "ERROR:linked list is empty\n";
    }
    while (temp != nullptr)
    {
        std::cout << "\n\n";
        std::cout << "Allocated Packet at Location:" << (void*)temp->location << "\n" << "size:" << temp->size << "\nRemaining memory:" << MemoryRem;
        temp = temp->next;
    }
    std::cout << "\n\n";
}