# Dining Philosophers Problem

## Overview
This project implements the Dining Philosophers Problem using POSIX semaphores in C. It demonstrates synchronization and concurrency control in a multi-threaded environment.

## Problem Description
Five philosophers sit at a round table with bowls of spaghetti. Forks are placed between each pair of adjacent philosophers. Each philosopher must alternately think and eat. A philosopher can only eat when they have both left and right forks. Each fork can be held by only one philosopher at a time.

## Features
- Semaphore-based synchronization
- Deadlock prevention using N-1 philosopher strategy
- Thread management for philosophers

## Getting Started
To compile and run the program:
bash
gcc -o dining_philosophers Bernard_Ginn_3.c -lpthread
./dining_philosophers
License
## Implementation Details
- Uses semaphores to manage chopstick availability
- Limits the number of philosophers picking up chopsticks to prevent deadlock
