#include "memory_manager_base.h"
#include <string.h>
#include <iostream>

// For example:
// start: 0 length: 5 name: A
// start: 5 length: 20 name: B
void MemoryManagerBase::print()
{
    list<memory_block>::iterator ptr;
    for (ptr = m_blocks.begin(); ptr != m_blocks.end(); ++ptr)
    {
        cout << "start: " << ptr->m_size << " length: " << ptr->m_size << " ";
        cout << "name: " << ptr->m_name << endl;
    }
}

