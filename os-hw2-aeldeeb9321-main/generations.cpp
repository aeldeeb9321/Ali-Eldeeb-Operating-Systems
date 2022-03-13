#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>

#include <iostream>

using namespace std;


// Given a number, this function should print the associated generation 
// of the child. along with the child's process ID and the parent's process ID.
// 
// Generations should be:
// 0 - Parent
// 1 - Child
// 2 - Grandchild
// 3 - Great Grandchild
// 4 - Great Great Grandchild
// etc.
//
// Examples:
//
//   printGeneration(1): Child. pid: <pid>: ppid: <ppid>
//   printGeneration(3): Great Grandchild. pid: <pid> ppid: <ppid>
//


    //       Example output:
    //      $ ./generations 5
    //      Great Great Great Grandchild. pid: 4569 ppid: 4568
    //      Great Great Grandchild. pid: 4568 ppid: 4567
    //      Great Grandchild. pid: 4567 ppid: 4566
    //      Grandchild. pid: 4566 ppid: 4565
    //      Child. pid: 4565 ppid: 4564
    //      Parent. pid: 4564 ppid: 3329

void printGeneration(int generation)
{
    if (generation >= 2)
    {
        for (int i = 0; i < generation - 2; i++)
        {
            cout << "Great ";
        }
        cout << "Grandchild. pid: " << getpid() << " " << "ppid: " << getppid() << endl; 
    }
    else
    {
        if (generation == 0)
        {
            cout << "Parent. pid: " << getpid() << " " << "ppid: " << getppid() << endl; 
        }
        else
        {
            cout << "Child. pid: " << getpid() << " " << "ppid: " << getppid() << endl; 
        }
    }
}


int main(int argc, char ** argv)
{
    // TODO: The program should take a single numeric command line argument, which 
    //       indicates how many generations to process. 
    //
    //       Retrieve this argument from the command line here.
    //       If there is no command line argument, or if the argument is less than 0,
    //       print an error and exit with a non-zero exit code.

    if (argc == 1)
    {
        cout << "Usage: " <<  argv[0] << " num_generations"<< endl;
        exit(1);
    }
  
    if (stoi(argv[1]) <= 0)
    {
        cout << "Error: num_generations must be greater than 0" << endl;
        exit(1);
    }

    // TODO: Implement the main logic of your program here.
    //       The program should use fork() to create a new child process
    //       for each generation, up to the number of generations indicated
    //       by the command line argument.
    //
    //       Each process (including the parent) should print their generation
    //       using the printGeneration() function above *in reverse order* 
    //       (so the last generation prints first).
    //
    //       Example output:
    //      $ ./generations 5
    //      Great Great Great Grandchild. pid: 4569 ppid: 4568
    //      Great Great Grandchild. pid: 4568 ppid: 4567
    //      Great Grandchild. pid: 4567 ppid: 4566
    //      Grandchild. pid: 4566 ppid: 4565
    //      Child. pid: 4565 ppid: 4564
    //      Parent. pid: 4564 ppid: 3329

    int num_generations = stoi(argv[1]);
    pid_t x = fork();

    int counter = 0;

    if (x == 0)
    {
        for (int i = 0; i < num_generations - 1; i++)
        {
            if (x == 0)
            {
                x = fork();
                counter++;
            }
        }

        if (x == 0)
            printGeneration(counter + 1);

        else
        {
            wait(NULL);
            printGeneration(counter);
        }
    }
    else
    {
        wait(NULL);
        printGeneration(counter);
    }
    return 0;
}