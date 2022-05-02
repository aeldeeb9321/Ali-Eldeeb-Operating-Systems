#include "memory_manager_base.h"
#include "memory_manager_first_fit.h"
#include "memory_manager_best_fit.h"

#include <iostream>
#include <fstream>
#include <string>
#include <unistd.h>

using namespace std;

int main(int argc, char ** argv)
{
    MemoryManagerBase *memory;   // Memory Manager that will be used 
    string algorithm;             // String choosing which memory manager to use
    int memory_size;              // Amount of memory to allocate

    algorithm = argv[1];
    memory_size = atoi(argv[2]);

    if (memory_size <= 0)
    {
        cerr << "Memory size which is " << argv[3] << " lower than or equal to zero." << endl;
        return(6);
    }
   
    if (algorithm == "first_fit"){ 
        memory = (MemoryManagerBase *) new MemoryManagerFirstFit(memory_size);
    }
    else if (algorithm == "best_fit"){
        memory = (MemoryManagerBase *) new MemoryManagerBestFit(memory_size);
    }
    else{
        cerr << "Please choose first_fit or best_fit method for the allocation type" << endl;
        return(6);
    }

    memory->print();

    ifstream in(argv[3]);

    if (!in.good()) 
    {
        cerr << "Failed to open file " << argv[3] << endl;
        return(6);
    }   

    while(in.good())
    {
        string line;
        getline(in, line);
        
        char operation_type[15];
        string name;
        char op_size[4];
        int counter = 0;
        int ctr_2 = 0;

        if (line[0] == 'a')
        {
            strcpy(operation_type, "allocate");
            for(int i = 0; i < sizeof(line); i++)
            {
                if ((line[i] == '\n') || (line[i] == '\0'))
                    break;

                if ((counter == 1) && (line[i] != ' '))
                {
                    op_size[ctr_2] = line[i];
                    ctr_2++;
                }
                if ((counter == 2) && (line[i] != ' '))
                    name = line[i];
                if (line[i] == ' ')
                    ++counter;
            }
            int operation_size = atoi(op_size);
            unsigned x = memory->allocate(operation_size, name);
            if (x == -1){
                cout << "Error during the allocation where size: ";
                cout << operation_size << " and name: " << name << endl;
            }
        }        
        else
        {
            strcpy(operation_type, "release");
            for(int i = 0; i < sizeof(line); i++)
            {
                if ((line[i] == '\n') || (line[i] == '\0'))
                    break;

                if ((counter == 1) && (line[i] != ' '))
                    name = line[i];
                if (line[i] == ' ')
                    ++counter;
            }
            unsigned x = memory->release(name);
            if (x == -1){
                cout << "Error during the release for " << name << " memory block" << endl;
            }
        }

        memory->print();
        cout << endl;
        if (in.eof())
        {
            break;
        }
    }
    return 0;
}