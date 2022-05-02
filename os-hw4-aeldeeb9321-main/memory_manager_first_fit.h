#ifndef MEMORY_MANAGER_FIRST_FIT_H
#define MEMORY_MANAGER_FIRST_FIT_H

#include "memory_manager_base.h"
// memory_manager_first_fit.h
//
// Class implementing a first fit memory allocation algorithm

class MemoryManagerFirstFit : public MemoryManagerBase {

    public:
        MemoryManagerFirstFit(int size);

        // Allocate the indicated amount of memory.
        // See the comments in memory_manager_base.h for details
        virtual int allocate(int size, string name);

        // Release the memory at the given location.
        // See the comments in memory_manager_base.h for details
        virtual bool release(string name);
        
    private:
    
};

#endif