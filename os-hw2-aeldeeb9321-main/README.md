# Operating Systems Assignment 2 - Generations
This exercise involves printing out the generations of a series of processes created using fork().

You will create a program that accepts a single command line argument indicating the number of generations that should be created. For each generation, your program will fork a child process until you have created a series of children of the right length. Each process should print its own generation, in reverse order.

When the generations are printed, each process should print its own process ID, as well as the process ID of its parent process.

## Example Output
Here are some sample runs:

### No argument
If no argument is provided, the program should print a message and exit

```
$ ./generations
Usage: ./generations num_generations
```
### Invalid argument
If the argument is less than 0, the program should print a message and exit
```
$ ./generations -1
Error: num_generations must be greater than 0
$
```
### Correct Argument
```
$ ./generations 5
Great Great Great Grandchild. pid: 5732 ppid: 5731
Great Great Grandchild. pid: 5731 ppid: 5730
Great Grandchild. pid: 5730 ppid: 5729
Grandchild. pid: 5729 ppid: 5728
Child. pid: 5728 ppid: 5727
Parent. pid: 5727 ppid: 3329
```
## Completing the Assignment
To complete the assignment, follow the same steps that you did in [Assignment 1](https://github.com/skamens-fordham/os-hw1-template/blob/main/README.md):

1. Accept the assignment in Github Classroom via [this link](https://classroom.github.com/a/94_ZqEEe)
2. Clone your repository to your local machine
3. Implement the code, following the instructions in the file `generations.cpp`
4. Compile and test your program. *Note:* It is not unusual when testing programs that use fork() to end up with an infinite loop. If this happens when you are testing, use Control-C to stop the execution and figure out what is causing the loop.
5. Commit your changes to git (`git commit`)
6. Push your changes to github (`git push`)
7. Complete the `submit.txt` file and upload it to Blackboard
