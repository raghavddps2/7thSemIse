1. OpenMp: An API for writing multithreaded applications.

2. OpenMp

    1. A set of compiler directives and librray routines for parallel application porgrammes.
    2. It greatky simplifies writing parallel programs in Fortran, C and C++
    3. Standardizes last 20 years of SMP.

3. OpenMp Core Stack

    1. Most of the constructs in OpenMp are compiler directives.
        #pragma omp construct[clause[clause]]
        #pragma omp paralle num_threads(4)
    
    2. Function prototypes and types in the file
        #include <omp.h>
    
    3. Most openMp constructs apply to a structured block. A structured block is nothing but a block of one or more statements with one point of entry at the top and one point of exit at the bottom.

    4. It's OK to have an exit() within the structured block.

4. OpenMp overview:

    1. OpenMp is a multi threading shared address model, THreads communicate by sharing variables.

    2. Unintended sharing of data causes race conditions. When programs outcome changes as threads are scheduled differently.

    3. Syncronization is expensive, so we need to change how data is accessed to minimize the need for synchronization.


5. Shared Memory Computer

    Any computer composed of multiple processing elements that share an address space. There are two classes.

    1. Symmetric Multiprocessor (SMP): A shared address space with "equal-time" access for each processor, and the OS treats every processor in the same way.

    2. Non Uniform Memory Access (NUMA): Different memory regions have different access costs, we can think of memory segmented into "Near" and "Far" memory.
    
6. Programming Shared Memory computers

    1. Process:
        An instance of program execution
        The execution context of a running program, i.e the resources associated with a running program
    
    2. All threads have the same data, text and the heap region but the threads have different stack memory, and has its own programs pointers

    3. General information

        1. An instance of a program. One process and lots of threads.
        2. Threads interact through reads/writes to a shared address spac.
        3. OS Scheduler decides when to run which threads, interleaved in fairness.
        4. Synchronization to assure every legal order results in correct results.

7. Fork - Join Parallelism

    1. The program starts as a single thread and at certain point during the execution it comes across situations where more threads are required, so master thread splits up into a number of threads, we call that collection of threads as a team of threads.

    2. When it is finished we are left with one thread again.

    3. A thread can forecast its own team of threads. The only way to create thread in OpenMp is with the parallel construct.

    4. It is pragma that basically tells the compiler to do something.In that backend, pragma is being translated into pthreads and then pthreads are being joined.
