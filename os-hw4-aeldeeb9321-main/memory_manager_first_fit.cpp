#include "memory_manager_first_fit.h"
#include <string>
#include <cstring>

using namespace std;

MemoryManagerFirstFit::MemoryManagerFirstFit(int size)
{
    memory_block *b = new memory_block;

    b->m_size = size;
    b->m_name = "init";
    b->m_mem_starting_point = new int(size);

    m_blocks.push_back(*b);
}

int MemoryManagerFirstFit::allocate(int size, string name) 
{
    list<memory_block>::iterator ptr;
    ptr = m_blocks.begin();    
    for (ptr; ptr != m_blocks.end(); ++ptr)
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
                }
                return *(ptr->m_mem_starting_point);
            }
        }
    }
    return -1;
}

bool MemoryManagerFirstFit::release(string name) 
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




