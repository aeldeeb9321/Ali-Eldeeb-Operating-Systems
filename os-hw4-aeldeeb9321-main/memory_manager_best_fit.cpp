#include "memory_manager_best_fit.h"
#include <string>

using namespace std;

MemoryManagerBestFit::MemoryManagerBestFit(int size)
{
    memory_block *b = new memory_block;
    b->m_size = size;
    b->m_name = "init";
    b->m_mem_starting_point = new int(size);
    m_blocks.push_back(*b);
}

int MemoryManagerBestFit::allocate(int size, string name) 
{
    list<memory_block>::iterator ptr;
    list<memory_block>::iterator temp;
    unsigned temp_size = 60000;
    ptr = m_blocks.begin();
    for (ptr; ptr != this->m_blocks.end(); ++ptr)
    {
        if ((ptr->m_name.compare("") == 0) || (ptr->m_name.compare("init") == 0))
        {
            if (ptr->m_size < size)
            {
                continue;
            }
            else if (ptr->m_size == size)
            {
                ptr->m_name = name;
                ptr->m_size = size;
                return *(ptr->m_mem_starting_point);
            }
            else if (ptr->m_size > size)
            {
                if (ptr->m_size < temp_size)
                {
                    temp = ptr;
                    temp_size = ptr->m_size;
                }    
            }
        }
    }

    ptr = temp;
    if (ptr->m_name == "init")
    {
        unsigned total_size = ptr->m_size;
        ptr->m_size = size;
        ptr->m_name = name;

        memory_block *nm = new memory_block;
        nm->m_size = total_size - size;
        nm->m_name = "init";
        nm->m_mem_starting_point = ptr->m_mem_starting_point + size;
        m_blocks.push_back(*nm);                  
        return *(ptr->m_mem_starting_point);
    }
    else
    {
        unsigned tmp = ptr->m_size;
        ptr->m_name = name;
        ptr->m_size = size;
            
        memory_block *nm = new memory_block;
        nm->m_size = tmp - size;
        nm->m_name = "";
        nm->m_mem_starting_point = ptr->m_mem_starting_point + size;
        m_blocks.insert(++ptr, *nm);
        --ptr;
        return *(ptr->m_mem_starting_point);
    }
    return -1;
}

bool MemoryManagerBestFit::release(string name) 
{
    list<memory_block>::iterator ptr;
    ptr = m_blocks.begin();
    unsigned size;
    bool release_flag = 0;
    for (ptr; ptr != m_blocks.end(); ++ptr)
    {
        if (ptr->m_name.compare(name) == 0)
        {
            ptr->m_name = "";
            size = ptr->m_size;
            release_flag = 1;
        }
    }
    ptr->m_size += size;
    return release_flag;
}



