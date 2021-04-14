# philosophers
My attemt on solving philosophers problem

Each one of the three programs is built using `make`

Also each is started by

`./philo_(one|two|three) <number of philosophers> <time to die (ms)> <time to eat (ms)> <time to sleep (ms)> [minimum times to eat]`

## Rules
There are some number of philosophers sitting around the table. They can only do one action at a time: eat, sleep, think. Each one does these action in a cycle.

To eat a philosopher needs two exactly two forks. Number of forks equals number of philosophers.
If a philosopher does not eat `<time to die>` ms, he dies and simulation stops.
Simulation also stops when all the philosophers ate at least `[minimum time to eat]` if specified.

### philo_one
Each philosopher is a thread. Forks are placed between philosophers. Syncronization is acomplished using mutexes.

### philo_two
Each philosopher is a thread. Forks are taken from a pool. Syncronization is acomplished using semaphores.

### philo_three
Same as previous but each philosopher is a process
