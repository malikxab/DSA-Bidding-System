# Auction System – C++ (3rd Semester DSA Project)

This project is a console-based Auction System developed as part of a 3rd-semester Data Structures and Algorithms (DSA) course.
The system simulates a real-time auction using core DSA concepts such as Binary Search Trees, Circular Queues, Vectors, and timer-based input handling.

---

## Features Implemented

### 1. User Registration (BST)

* Users are stored in a Binary Search Tree (BST).
* Enables fast search and alphabetical display of all registered users.
* Prevents duplicate registration.
* The code includes an in-order traversal for listing users alphabetically.

### 2. Auction Queue (Circular Queue)

* Implements a circular queue using an array and modular indexing.
* Users join the queue in FIFO order.
* A user cannot join twice; duplicate entries are blocked.
* The queue rotates until each user has one chance to bid.
* The circular queue implementation includes:

  * enqueue
  * dequeue
  * isFull
  * isEmpty
  * exists (checks if a user is already in queue)

### 3. Timed Bidding (5-Second Input Window)

* Each participant has 5 seconds to enter a bid.
* Implemented using:

  * chrono (steady_clock)
  * conio.h (_kbhit and _getch)
* If no input is entered within the time limit, the turn is skipped.

### 4. Bid Validation Logic

The system enforces the following real auction rules:

* A user **must place an initial bid** higher than 0.
* Every next bid must be **strictly greater** than the current highest bid.
* If a user enters a smaller or equal bid, the turn is skipped.
* Bids are only accepted if valid and within time.

### 5. Turn-Based Auction Using Queue

The auction proceeds in order:

* Each user gets one turn in FIFO order (Circular Queue).
* If the user fails to bid:

  * due to timeout, or
  * due to low bid
    their turn is skipped.
* The auction ends when:

  * everyone has taken a turn, or
  * all remaining turns result in skips (meaning no higher bid is placed)

### 6. Highest Bid Tracking

* Stores the highest bid amount and the username of the highest bidder.
* Updated only when a valid bid is placed.
* Highest bid can be viewed any time.

### 7. Bid History Tracking

* A vector stores all accepted bids in the format:
  username → amount
* The full history can be displayed from the menu.

### 8. Display Functions

The program supports displaying:

* Queue contents
* Highest bid
* Complete bid history
* Registered user list (in alphabetical BST order)

---

## Data Structures and Algorithms Used

1. Binary Search Tree (BST)

   * Used for storing and searching registered users.
   * Also used to display users alphabetically using in-order traversal.

2. Circular Queue (Array-Based)

   * Used to manage turn order during the auction.
   * Implements wrap-around indexing with modular arithmetic.

3. Vector

   * Stores bid history dynamically.

4. Timer-Based Input

   * Implemented using the chrono library and conio.h.

5. Basic OOP Principles

   * Custom classes for Queue and BST.
   * Encapsulation of data structure operations.

---

## Programming Language and Libraries

* Language: C++
* Standard Libraries Used:

  * iostream
  * string
  * vector
  * chrono
* Additional Library:

  * conio.h (for low-level keyboard input detection)

---

## Summary

This is a complete 3rd-semester DSA project showcasing:

* Implementation of classical data structures
* Real-time input handling
* Logical flow control for an auction system
* Interactive menu-driven architecture

