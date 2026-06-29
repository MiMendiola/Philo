<p align="center">
  <img src="https://raw.githubusercontent.com/ayogun/42-project-badges/main/badges/philosopherse.png" alt="Philosophers Badge"/>
</p>

<h1 align="center">🍝 Philosophers</h1>

<p align="center">
  <strong>I never thought philosophy would be so deadly</strong><br>
  Simulation of the classic dining philosophers problem using threads and mutexes
</p>

<p align="center">
  <img src="https://img.shields.io/badge/Language-C-blue?style=for-the-badge&logo=c" />
  <img src="https://img.shields.io/badge/Threads-pthreads-orange?style=for-the-badge" />
  <img src="https://img.shields.io/badge/School-42_Madrid-black?style=for-the-badge&logo=42" />
  <a href="../../README.md">
    <img src="https://img.shields.io/badge/Leer_en-Español-purple?style=for-the-badge" alt="Leer en Español" />
  </a>
</p>

---

## 📋 Table of Contents

- [About the Project](#-about-the-project)
- [Features](#-features)
- [Requirements](#-requirements)
- [Installation](#-installation)
- [Usage](#-usage)
- [Simulation Rules](#-simulation-rules)
- [Synchronization](#-synchronization)
- [Technical Features](#-technical-features)
- [Project Structure](#-project-structure)
- [Resources](#-resources)

---

## 🎯 About the Project

**Philosophers** is a 42 cursus project that implements the classic dining philosophers problem. Several philosophers sit around a table and alternate between eating, sleeping, and thinking. To eat, each philosopher needs two forks shared with their neighbors.

The goal is to understand:

- **Threads** with `pthread`.
- **Mutexes** to protect shared resources.
- **Data races** and how to avoid unsafe reads and writes.
- **Deadlocks** and resource-ordering strategies.
- **Timing** in a concurrent simulation.

---

## ✨ Features

### Core Features

- ✅ One thread per philosopher
- ✅ Monitor thread to detect deaths
- ✅ One mutex per fork
- ✅ Mutexes for output and global state
- ✅ Synchronized start for all threads
- ✅ Special handling for one philosopher
- ✅ Optional maximum meal count
- ✅ Clean thread and mutex shutdown

### Argument Validation

- ✅ Positive numbers only
- ✅ Negative values rejected
- ✅ Non-numeric characters rejected
- ✅ Protection against values greater than `INT_MAX`
- ✅ Correct argument-count validation

---

## 🛠️ Requirements

- **Operating System**: Linux or macOS
- **Compiler**: `cc`, `gcc`, or `clang`
- **Make**
- **Libraries**:
  - `pthread`
  - `sys/time`

---

## 📦 Installation

```bash
git clone https://github.com/MiMendiola/Philo.git
cd Philo
make
./philo 5 800 200 200
```

### Available Make Commands

```bash
make        # Compiles philo
make clean  # Removes object files
make fclean # Removes object files and executable
make re     # Rebuilds from scratch
```

---

## 🚀 Usage

```bash
./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]
```

| Argument | Description |
| --- | --- |
| `number_of_philosophers` | Number of philosophers and forks |
| `time_to_die` | Maximum time without eating before death, in ms |
| `time_to_eat` | Time spent eating, in ms |
| `time_to_sleep` | Time spent sleeping, in ms |
| `number_of_times_each_philosopher_must_eat` | Optional. Simulation ends when all philosophers reach this count |

### Examples

```bash
./philo 1 800 200 200
./philo 5 800 200 200
./philo 5 800 200 200 7
./philo 4 410 200 200
```

---

## 🍽️ Simulation Rules

Each philosopher repeats this cycle:

```text
take one fork
take the other fork
eat
release both forks
sleep
think
```

The simulation ends when:

- A philosopher exceeds `time_to_die` without eating.
- Every philosopher reaches the required meal count, if the fifth argument was provided.

---

## 🔐 Synchronization

Each fork is a `pthread_mutex_t`. To reduce deadlock risk, fork assignment changes depending on the philosopher id:

```text
Odd philosophers:
  left_fork  -> next fork
  right_fork -> current fork

Even philosophers:
  left_fork  -> current fork
  right_fork -> next fork
```

The monitor waits until all philosopher threads are running, then repeatedly checks whether any philosopher has died.

---

## 🔬 Technical Features

```c
typedef struct s_philo
{
    int             id;
    pthread_t       thread_id;
    int             meals;
    bool            full;
    long            last_meal;
    t_fork          *left_fork;
    t_fork          *right_fork;
    pthread_mutex_t mutex;
    t_table         *table;
}   t_philo;
```

Key functions:

```c
int     init_table(t_table *table, char *av[]);
void    init_data(t_table *table);
void    simulation_start(t_table *table);
void    *simulation_dinner(void *data);
void    *simulation_monitor(void *data);
void    eat(t_philo *philo);
```

---

## 📁 Project Structure

```text
Philo/
├── Makefile
├── README.md
├── includes/
│   └── philo.h
└── src/
    ├── actions.c
    ├── getters_setters.c
    ├── handlers.c
    ├── init.c
    ├── philo.c
    ├── philo_lib.c
    ├── philo_utils.c
    ├── simulation.c
    └── syncro.c
```

---

## 📚 Resources

- [pthread_create(3)](https://man7.org/linux/man-pages/man3/pthread_create.3.html)
- [pthread_mutex_lock(3)](https://man7.org/linux/man-pages/man3/pthread_mutex_lock.3p.html)
- [pthread_join(3)](https://man7.org/linux/man-pages/man3/pthread_join.3.html)
- [Dining Philosophers Problem](https://en.wikipedia.org/wiki/Dining_philosophers_problem)
- [gettimeofday(2)](https://man7.org/linux/man-pages/man2/gettimeofday.2.html)

---

## 🎓 Key Learnings

- **Concurrent programming** with threads.
- **Synchronization** with mutexes.
- **Deadlock prevention** through resource-ordering.
- **Shared-state protection** to avoid data races.
- **Timing** in millisecond-sensitive simulations.
- **Resource cleanup** in multithreaded programs.

---

## 👥 Authors

- **Miguel** - [@MiMendiola](https://github.com/MiMendiola)

---

## 📄 License

This project is part of the 42 Madrid cursus and follows its academic rules.

---

<p align="center">
  <sub>Developed with C and pthreads at 42 Madrid</sub>
</p>
