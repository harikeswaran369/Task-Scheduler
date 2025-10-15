# Task-Scheduler
This repo contains implementing task scheduler from scratch using ARM-M4 processor based STM32F407 Discovery Development board

# Implementing a Preemptive Task Scheduler on ARM Cortex-M4

A bare-metal **preemptive task scheduler** implemented from scratch on an **ARM Cortex-M4 microcontroller** (STM32).
This project builds a **mini-RTOS-like kernel** without using FreeRTOS or any external libraries — handling **task management, context switching, and scheduling** entirely through manual stack manipulation and exception handling.

---

## Project Overview

The goal of this project was to design and implement a **round-robin preemptive scheduler** capable of running multiple independent tasks with context preservation.
Each user task has its own stack, state, and delay mechanism, allowing efficient CPU utilization similar to a real-time operating system (RTOS).

The system uses:

* **SysTick** timer interrupts to generate periodic ticks (1 ms),
* **PendSV** exceptions for context switching,
* **PSP/MSP** stack pointer separation for user and kernel modes,
* **Task Control Blocks (TCBs)** to track task states and stack pointers.

---

## Features

* **Round-Robin Preemptive Scheduling**
  All tasks share CPU time equally, managed via SysTick interrupts and PendSV exceptions.

* **Task Control Block (TCB) Architecture**
  Each task maintains its own private stack, program counter, and state (Ready / Blocked).

* **Timer-Based Task Delay (Blocking Mechanism)**
  Tasks can voluntarily yield the CPU for a defined duration (`task_delay()`), improving efficiency.

* **Idle Task Implementation**
  Runs only when all user tasks are blocked — useful for low-power modes.

* **Context Switching**
  Fully manual saving and restoring of registers (R4-R11 + stack frame) during task switches.

* **LED Blinking Demonstration**
  Four LEDs toggle at independent rates, showcasing parallel task scheduling behavior.

---

## System Architecture

**Core Components:**

* `main.c` — Initializes system stack, SysTick, tasks, and context switching routines. (conceptually integrated) — Scheduler, PendSV handler, SysTick handler, delay and unblocking logic.
* `led.c / led.h` — Peripheral control for LEDs (GPIO configuration and toggling).

**Execution Flow:**

1. Initialize processor faults and SysTick timer (1 ms tick).
2. Create and initialize stacks for all tasks.
3. Switch from **MSP (Main Stack Pointer)** to **PSP (Process Stack Pointer)**.
4. Enter task handler for the first task.
5. SysTick triggers periodic PendSV exceptions → scheduler decides the next ready task.

---

## Task Demonstration

| Task      | LED Color | Blink Rate | Description                               |
| --------- | --------- | ---------- | ----------------------------------------- |
| Task-1    | Green     | 1 s        | Toggles every second                      |
| Task-2    | Orange    | 0.5 s      | Toggles twice per second                  |
| Task-3    | Blue      | 0.25 s     | Fast blink                                |
| Task-4    | Red       | 0.125 s    | Rapid blink                               |
| Idle Task | —         | —          | Executes when all other tasks are blocked |

Each LED’s toggle pattern verifies successful scheduling and context switching.

---

## Technical Concepts Demonstrated

* ARM Cortex-M **exception handling mechanism**
* **Stack frame manipulation** and context preservation
* **PendSV**-based deferred interrupt scheduling
* **SysTick timer** configuration and ISR chaining
* **Preemptive multitasking** in bare-metal C
* **Fault management** using HardFault, BusFault, MemManage handlers
* **Register-level GPIO programming**

---

## Tools and Environment

* **MCU:** STM32F4xx (ARM Cortex-M4 core)
* **Language:** C (bare-metal, no RTOS)
* **IDE:** STM32CubeIDE / ARM GCC Toolchain
* **Debugger:** ST-Link 
* **Clock Frequency:** 16 MHz
* **Tick Rate:** 1 kHz (1 ms SysTick interval)

---

## Key Learning Outcomes

* Building a mini RTOS kernel from scratch
* Understanding **stack models** and **context management**
* Implementing **blocking delays** via system ticks
* Using **exception priorities** for deterministic scheduling
* Debugging fault handlers and register states in real-time

---

## Demo Output (Expected Behavior)

All four LEDs blink concurrently at their respective rates, even though only one is executing at any instant — proving correct **task preemption** and **context restoration**.

---

## 📚 References

* ARMv7-M Architecture Reference Manual
* STM32F4 Reference Manual (RM0090)
