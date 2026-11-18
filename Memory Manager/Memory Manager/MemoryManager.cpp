#include "MemoryManager.h"

MemoryManager::MemoryManager(size_t size)
{
	address = malloc(size);
}

MemoryManager::~MemoryManager()
{
	if (address != nullptr) 
	{
		free(address);
		address = nullptr;
	}
}


//TODO FOR MIN PRODUCT:
//take away temp->loc + temp-> size from temp->next>location to find the abount of bytes between them
//when creating a new packet, check thorough the empty spaces to see if it will fit instead of slotting at the end.

void* MemoryManager::AllocateMemory(size_t size)
{
    
    if (head == nullptr)
    {
        //makes head packet
        MetaData* data = (MetaData*)(address);
        //populate the first data packet
        data->location = (byte*)address + sizeof(MetaData);
        data->size = size + sizeof(MetaData);
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
        //checks if there is space between 2 packets
        if (temp->next != nullptr)
        {
            size_t spaceleft = ((size_t)(temp->next->location) - (size_t)(temp->location + temp->size));
            if (spaceleft > 0) 
            {
                //checks if the new packet will fit in said space
                if (size < spaceleft) 
                {
                    std::cout<< "spaceleft:" << spaceleft << "\n";
                    MetaData* data = (MetaData*)(temp + temp->size);
                    data->location = temp->location + temp->size;
                    data->size = size + sizeof(MetaData);
                    data->next = temp->next;
                    temp->next = data;
             
                    return data->location;
                    //slot the new packet into the space
                }
            
            }
        }
        temp = temp->next;
    }

    //allows to set new packet at the end of linked list

    MetaData* data = (MetaData*)(temp->location + temp->size - sizeof(MetaData));

    //std::cout << "size+loc:" << (int)(temp->location + temp->size);
    data->location = temp->location + temp->size;
    data->size = size + sizeof(MetaData);
    data->next = nullptr;
    //sets next data 
    temp->next = data;



    return data->location;
}


void MemoryManager::DeallocateMemory(void* del)
{
    //grabs head
    MetaData* temp = head;
    //deallocate if mem is in head
    if (head->location == del) 
    {
        //cahce head
        MetaData* todel = head;
        //set head to next value
        head = temp->next;
        //delete cached head
       

        std::cout << "deleted head\n";
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
            //relinks the list
            temp->next = temp->next->next;

            std::cout << "deleted mid list\n";

          
            return;
        }        
        std::cout << "nothing to delete";        
    }
}

void MemoryManager::Output()
{
    //output (always last thing to do)
    MetaData* temp = head;
    while (temp != nullptr)
    {
        std::cout << "\n";
        std::cout << "packetloc" << (void*)temp << "\n";
        std::cout << "loc" << (void*)temp->location << "\n";
        std::cout << "endloc:" << (void*)(temp->location + temp->size) << "\n";
        std::cout << "total size:" << (temp->size) << "\n";
        std::cout << "size of packet:" << (temp->size - sizeof(MetaData)) << "\n";
        temp = temp->next;
    }
    std::cout << "\n\n\n";
}