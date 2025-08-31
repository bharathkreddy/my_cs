# Project 2: Hospital Emergency System (Queues)

## Core Concept

Create a comprehensive hospital emergency room management system that handles patient flow, resource allocation, and staff scheduling using different queue types.

## Key Features \& Operations

- **Triage System**: Priority queue based on medical urgency
- **Patient Flow**: FIFO queues for different departments
- **Appointment Scheduling**: Circular queues for recurring slots
- **Resource Management**: Deque for flexible resource allocation
- **Staff Rotation**: Queue-based shift management
- **Ambulance Dispatch**: Priority queue with real-time updates


## Real-World Applications

- Operating system process scheduling
- Print job management
- Network packet routing
- Call center management
- Traffic light systems


## Operations Covered

- Enqueue/Dequeue operations
- Priority queue operations
- Circular queue implementation
- Double-ended queue (deque) operations
- Queue merging and splitting
- Dynamic queue resizing

***
NOTE: I have taught a few people queues using below methodology.

Here’s a step-by-step learning path to build a **Hospital Emergency System in C**, focusing on core queue concepts and best practices. Each step includes objectives, hints, and learning outcomes. The project steps gradually introduce complexity and idiomatic C patterns, helping reinforce key concepts.

***

## Step 1: Foundation - Define Data Structures and Basic Queues

**Objectives:**
- Design clean `struct`s for patients, resources, and staff.
- Implement a simple FIFO queue for patients using a linked list.

**Hints:**
- Use `typedef struct` for clarity and maintainability.
- Encapsulate queue operations (`enqueue`, `dequeue`) in functions; avoid global variables.
- Start with fixed-size patient records (name, age, severity, etc.).

**Learning Focus:**
Memory management, separation of concerns, C struct basics, function design.

***

## Step 2: Priority Queue for Triage & Ambulance Dispatch

**Objectives:**
- Convert FIFO queue to a priority queue for triage using medical urgency, and similar for ambulance dispatch.
- Implement insertion and removal based on priority (highest urgency first).

**Hints:**
- Use a **heap** or sorted linked list for managing priorities.
- Emphasize modularity by separating triage logic from patient records.
- Think about edge cases: what if queues are empty or full?

**Learning Focus:**
Algorithm implementation, comparison logic, defensive coding, modularity.

***

## Step 3: Circular Queue for Appointment Scheduling

**Objectives:**
- Model recurring appointment slots with a circular queue, allowing scheduling and cancellation.

**Hints:**
- Use arrays for circular queues; manage `front` and `rear` indices using modulo arithmetic.
- Carefully handle overflow and underflow conditions (“queue full”, “queue empty”).
- Refactor code for reusable queue types—don’t repeat basic operations between queue types.

**Learning Focus:**
Pointer arithmetic, array manipulation, error handling, code reuse.

***

## Step 4: Resource Management via Deque

**Objectives:**
- Use a double-ended queue to manage resources that can be allocated or released from either end (e.g., beds or equipment).

**Hints:**
- Extend queue structs to support `enqueue_front` and `enqueue_rear`.
- Demonstrate operations for both directions (removal/addition).
- Test for memory leaks and properly free memory after operations.

**Learning Focus:**
Flexibility in data structures, pointer operations, resource cleanup.

***

## Step 5: Staff Rotation with Shift Queues

**Objectives:**
- Build a queue to manage staff shift rotations, allowing for joining/leaving shifts in order.

**Hints:**
- Use a simple FIFO linked list; but challenge yourself by enabling merging/splitting of shifts (i.e., combine two queues or divide one).
- Write functions to merge queues and split them, focusing on pointer safety.

**Learning Focus:**
Advanced pointer manipulation, queue operations beyond basics, design for future expansion.

***

## Step 6: Dynamic Queue Resizing and Integration

**Objectives:**
- Allow queues (especially circular queues) to resize dynamically (increase if demand spikes).
- Integrate all sub-queues into a unified system for the hospital.

**Hints:**
- Use `malloc` and `realloc` for dynamic memory.
- Start bringing together triage, appointments, resource, and staff management.
- Organize your code into header files (`.h`) and implementation files (`.c`) for clarity.

**Learning Focus:**
Dynamic memory, modular design, code organization, system integration.

***

## Step 7: Error Handling, Testing & Documentation

**Objectives:**
- Test each queue operation with edge cases (overflow, underflow, merging/splitting).
- Handle errors gracefully—not just crashing on failure.
- Document your code with clear comments and README instructions.

**Hints:**
- Use `assert()` for development-time checks; return error codes on failures.
- Write simple main test cases to simulate hospital scenarios.
- Practice writing concise function comments and usage guides.

**Learning Focus:**
Robustness, code readability, defensive programming, documentation practices.

***

### Final Learning Outcomes

By following these steps, you’ll master **idiomatic C data structures**, memory management, queue algorithms, debugging, modular design, and error handling—all central to effective C programming in real-world systems. Each step encourages refactoring and gradual improvements that mirror professional software development practices.

