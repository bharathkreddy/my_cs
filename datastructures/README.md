# Data Structures
#### These are my notes on data structures, their time/space complexity & how to code them in these languages, ill keep adding languages as i learn 
    - C <- currently learning
    - C++ <- currently learning
    - Python <- proficient
    - JavaScript <- proficient
    - Java <- reasonable 
    - C#
    - Golang <- up next on learning
    - RUST <- wait and watch where this goes before investing time.

# Notes
1. A program is a set of instructions which operate on some data.
2. The way data is organised in main memory during exection of a program is called data structures.

# Types of Data Structures (running notes)
1. Physical data structures: how data is laid out in memory
    - [Arrays](./arrays)
    - [Strings](/.strings)
    - Matrices(./matrices)
    - Linked Lists
2. Logical data structures: How data is utilized
    - Stack
    - Queues
    - Trees
    - Graph
    - Hashing
3. Recursion
    - Tail recursion: 
        - If function calls itself as last statement in its body. 
        - All the work by function is done at calling time and nothing is done at returning time. 
        - Can be easily converted to while or for loops.
        - both loop and tail recursion would have time complexity O(n) but since recursions creates stacks the space complexity of loops are O(1) and tail recursion would be O(n).

    - Head recursion:
        - The first thing a function does is calling itself and then after it is all the work that the function has to do.
        - All the work of a function is done at return time.
        - cant be converted to a loop but not easily.
        - time complexity is same O(n) but space complexity of loops O(1) vs recursion O(n).

    - Tree recursion
        - if a function calls itself more than one time in same function call. 
        - If a function calls itself 2 times, you will see by drawing recursion tree that time complexity would be O(2^n), 
        - space complexity is however equal to height of the recursion tree i.e. O(n). Draw out a recursion tree for a simple example to prove this to yourself (because i know i will forget how i arrived at these calcs.)

    - Indirect recursion
        - If a function A calls function B and function B calls function A.
        - can be more than 2 as well ex: fnA -> fnB -> fnC -> FnA.

    - Nested recursion
        - if a function calls itself with a parameter which itself is a function.
        - fnA(n) -> fnA(fnA(n-1))
        
4. Sorting

