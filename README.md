# DSA_ASSIGNMENT_1

🧾 DSA Assignment 1 — Advanced ADTs and Simulations

Author: Hanan Majeed (519166)

Course: Data Structures and Algorithms

Instructor: Fahad Ahmad Satti

📘 Approach

the major hurdle was of class redefing error which was out of my thinking i tried different appreoaches but all in vain but here comes the email of using hidden keyword and i just click virtual and solved the problem.

Polynomial ADT:

Implemented using a linked list structure to store terms (coefficient, power). Each Polynomial object maintains its own linked list via a global map. Supports insertion, addition, multiplication, and derivative operations with proper merging and simplification.

Text Editor Simulation:

Designed with a doubly linked list representing text characters. The editor supports cursor movement, insertion, and deletion efficiently in O(1) time per operation. Properly handles boundary conditions like moving beyond start/end and deleting in an empty editor.

UNO Game Simulation:

A vector-based simulation of the UNO card game for 2–4 players. The game handles deck initialization (fixed seed for reproducibility), player turns, direction changes, and action cards (Skip, Reverse, Draw Two). Includes logic for UNO alerts, game-over detection, and stalemate handling.

All implementations strictly follow modular OOP design, adhere to the given header interfaces, and maintain the same coding style and brace formatting for consistency.

🌐 Public GitHub Repository

🔗(https://github.com/hanan1hub/DSA_ASSIGNMENT_1.git)


⚙️ Challenges Faced
Class redefining was the major one.

Managing memory and ownership in linked list–based structures without using STL containers.

Ensuring output formatting matched exactly the required format (especially for UNO state strings).

Handling edge cases such as zero coefficients in polynomials, cursor movement at boundaries in the text editor, and direction changes + action stacking in UNO.

Maintaining consistent behavior across different compilers (GCC, MinGW, VS Code) due to minor differences in warnings and random shuffle implementations.