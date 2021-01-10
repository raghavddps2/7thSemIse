1. Now, as we write programs with threads we notice that the time taken to execute the programs increases when threads increase. This is dude to the concept of False Sharing.

2. If independent data elements happen to sit on the same cache line, each update will cause the cache lines to "slosh back and forth" between threads. This is called as false sharing.

3. This results in poor scalability! So, we need to come up with a way so that the programs we write are more scalable. We make it a 2D array and we Pad it by 8 and then we have data sitting on different cache lines and hence resolves the problem of false sharing.

4. OpenMp Overview

    1. OpenMp is a multi-threading shared address model.
    2. Unintended sharing of data causes race conditions.
    3. To control race conditions, use synchronization to protect data outliers.
    4. Change how data is accessed to minimize the need for synchronization.

5. Synchronization

    1. Barrier synchromization: Wait till everyone arrives and then we can go on.
    2. Mutual Exclusion: Define a block of code that only one thread at a time can execute that block of code.
    3. #pragma omp parallel.
    4. #pragma omp barrier
    5. #pragma omp critical
    6. #pragma omp atomic