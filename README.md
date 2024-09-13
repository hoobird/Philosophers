## Philosophers Problem

---

### Description:
This project is an implementation of the classical **Dining Philosophers Problem** using C and pthreads. It simulates a group of philosophers sitting at a table with forks between them. Philosophers alternate between thinking, eating, and sleeping, but need two forks to eat, which introduces synchronization challenges to avoid deadlock and starvation.

---

### Overview:
The **Dining Philosophers Problem** highlights issues of synchronization in concurrent programming. Each philosopher requires two forks to eat, but only one fork is available on either side. The solution provided here manages the behavior of philosophers with careful use of mutexes to control access to shared resources (forks) while also monitoring the state of each philosopher to avoid deadlocks and starvation.

The project includes:
- A simulation of philosophers' behaviors (thinking, eating, sleeping)
- Proper synchronization using mutexes to avoid resource contention
- Thread monitoring to detect when philosophers starve or when the simulation ends

---

### Requirements/Prerequisites:
- **C Compiler** (such as GCC)
- **Pthreads Library** (POSIX threads, standard on most Unix-based systems)
- Basic knowledge of C and threading concepts
- (Optional) Make utility to simplify the compilation process

---

### Usage:
1. **Clone the repository:**
   ```bash
   git clone git@github.com:hoobird/Philosophers.git
   cd philosophers_problem
   ```

2. **Build the project:**
   If using `make`, run:
   ```bash
   make all
   ```

3. **Run the simulation:**
   The program takes 5 arguments:
   ```bash
   ./philo <number_of_philosophers> <time_to_die> <time_to_eat> <time_to_sleep> [optional: number_of_times_each_philosopher_must_eat]
   ```

   Example:
   ```bash
   ./philo 5 800 200 200
   ```

   This will run a simulation with 5 philosophers where:
   - Time to die: 800 ms
   - Time to eat: 200 ms
   - Time to sleep: 200 ms

4. **To clean up compiled files:**
   ```bash
   make clean
   ```

---

### Examples:
- **Run with 5 philosophers and no eating limit:**
   ```bash
   ./philo 5 800 200 200
   ```
- **Run with 4 philosophers, and each must eat at least 3 times:**
   ```bash
   ./philo 4 800 200 200 3
   ```

---

### Explanation:

1. **Philosopher Lifecycle**: Each philosopher alternates between three states:
   - **Thinking**: The philosopher is thinking and waiting for forks.
   - **Eating**: The philosopher picks up two forks (mutexes) and eats.
   - **Sleeping**: After eating, the philosopher sleeps for a defined period.

2. **Thread Synchronization**: 
   - Mutexes are used for forks to ensure that only one philosopher can pick up a fork at a time.
   - Each philosopher has their own thread, and careful monitoring prevents race conditions, deadlocks, or philosophers from starving.

3. **Game Over Condition**: 
   - The simulation ends if any philosopher dies (fails to eat within the given time to die) or if all philosophers have eaten the required number of times (if specified).

---

This simulation helps in understanding how to manage shared resources in concurrent programming and ensures synchronization while avoiding common pitfalls such as deadlocks and starvation.
