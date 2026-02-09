# Philosopher

A multithreaded simulation of the Dining Philosophers synchronization problem using POSIX threads and mutexes.

---

## 🎯 Overview

This project implements a solution to the classic **Dining Philosophers Problem** using POSIX threads and mutexes. The challenge is to prevent deadlock and starvation while philosophers compete for shared resources (forks) to eat spaghetti.

The simulation demonstrates fundamental concepts in concurrent programming:
- Thread creation and management
- Mutex-based synchronization
- Deadlock prevention strategies
- Race condition avoidance
- Precise timing and monitoring

---

## 🤔 The Problem

**N philosophers** sit at a round table, alternating between eating, thinking, and sleeping. Each needs **two forks** to eat, but there are only **N forks** (one between each pair). They don't communicate and the simulation ends on starvation or meal completion.

**Challenges:** Prevent deadlock (all grab one fork), starvation (some never eat), and data races on shared resources

---

## 🛠️ Implementation Details

### 1. **Microsecond Precision Timing**
Times internally stored in microseconds (converted from ms input), ensuring accuracy and meeting the 10ms death detection requirement.

### 2. **Custom Sleep Function**
Polling-based sleep that checks simulation state during delays, using adaptive intervals (500μs/100μs) for precision while allowing quick thread termination.

#### 3. **Deadlock Prevention Strategy**
**Even/odd fork acquisition ordering:**
```c
// Even philosophers: right fork → left fork
// Odd philosophers: left fork → right fork
```
This breaks the circular wait condition that causes deadlock.

#### 4. **Thread Synchronization**
All threads start simultaneously using a synchronization barrier:
```c
wait_for_all_start(mysettings);  // All threads wait for go signal
```

#### 5. **Starvation Prevention**
- **Odd philosophers start with a delay**: `usleep(z_die / 4)` to reduce initial contention
- **Extra thinking time for odd counts**: Balances the eating schedule when philosophers can't pair up evenly

---

## 📦 Installation

```bash
make          # Compile
make clean    # Remove objects
make fclean   # Remove objects + binary
make re       # Recompile
```

---

## 🚀 Usage

### Basic Syntax
```bash
./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_must_eat]
```

### Arguments
| Argument | Description | Unit |
|----------|-------------|------|
| `number_of_philosophers` | Number of philosophers (and forks) | count |
| `time_to_die` | Max time since last meal before death | milliseconds |
| `time_to_eat` | Time spent eating | milliseconds |
| `time_to_sleep` | Time spent sleeping | milliseconds |
| `[times_must_eat]` | Optional: simulation stops after N meals | count |

### Examples

```bash
./philo 5 800 200 200          # Should not die
./philo 5 800 200 200 7        # Stops after 7 meals each
./philo 4 410 200 200          # Tight timing
./philo 1 800 200 200          # Single philosopher (dies)
./philo 200 800 200 200        # Stress test
```

### Output Format
```
000042 3 has taken a fork
000042 3 is eating
000242 3 is sleeping
000442 3 is thinking
012345 2 died
```

---

## ✨ Key Features

- **Thread-safe operations**: Dedicated mutexes protect all shared resources (print, end flag, meal times, fork states)
- **Precise death detection**: Monitor thread polls every 500μs, detects death within 10ms requirement
- **Clean exit**: Threads check end flag frequently, allowing quick synchronized termination
- **Edge cases**: Handles single philosopher, zero meals, 200+ philosophers, input validation

---