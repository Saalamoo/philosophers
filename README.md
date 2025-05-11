# philosophers

## About

The **Philosophers** project is a concurrency exercise based on the famous **Dining Philosophers Problem**. The goal is to simulate philosophers who alternately eat, think, and sleep — without causing **deadlocks** or **race conditions**.

This project strengthens the understanding of:

- **Multithreading** using `pthread`
- **Mutexes** and how to protect shared resources
- Avoiding deadlocks, starvation, and data races
- Accurate **timing and synchronization**

Each philosopher has a fork on their left and right, and must take both to eat. The challenge is ensuring no philosopher starves or causes the simulation to freeze.

## Death Detection & Synchronization

To ensure the simulation runs correctly and deterministically, synchronization and death detection were carefully implemented using threads and mutexes:

- **Death Monitoring**: A separate thread (monitor) checks periodically if any philosopher has exceeded the `time_to_die` limit since their last meal. If a philosopher dies, the monitor prints the death message and safely stops the simulation.

- **Mutex Protection**: Shared resources like forks, printing to the terminal, and variables tracking eating times are protected using **mutexes** to prevent race conditions and undefined behavior in concurrent access.

- **Accurate Timing**: Timestamps are tracked using high-resolution time functions, and `usleep` is used for short delays without excessive CPU usage.

- **Safe Termination**: Once a philosopher dies or all required meals are completed, flags and mutexes ensure that threads stop gracefully without accessing freed or invalid memory.

This synchronization strategy helps simulate the dining philosophers problem realistically while avoiding deadlocks and starvation.

## Compilation

To compile the project, simply run:

```bash
make
```
This will generate the philo executable.


## Run

```bash
./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]

```

Parameters:
- number_of_philosophers: Total philosophers (and forks)
- time_to_die: Time before a philosopher dies without eating
- time_to_eat: Time a philosopher spends eating
- time_to_sleep: Time a philosopher spends sleeping
- number_of_times_each_philosopher_must_eat: (Optional) Ends simulation when each philosopher has eaten this many times

```bash
./philo 5 800 200 200

```
This starts 5 philosophers with the given timing constraints.

## Rules

- A philosopher must take **both forks** before eating.
- Forks are shared between neighbors and protected using **mutexes**.
- If a philosopher doesn’t eat within `time_to_die`, they **die** and the simulation ends.
- The simulation stops once a philosopher dies or all have eaten the required number of times (if specified).
