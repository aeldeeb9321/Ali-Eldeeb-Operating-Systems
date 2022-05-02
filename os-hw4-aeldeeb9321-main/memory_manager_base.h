#ifndef MEMORY_MANAGER_BASE_H
#define MEMORY_MANAGER_BASE_H

#include <list>
#include <string>
#include <string.h>

using namespace std;

class MemoryManagerBase {

    public:
        virtual int allocate(int size, string name) = 0;

        virtual bool release(string name) = 0;    

        virtual void print();

    
    protected:
        
        struct memory_block 
        {
            string m_name;
            int m_size;
            int *m_mem_starting_point;
        }; 

        std::list<struct memory_block> m_blocks;
};

#endif
