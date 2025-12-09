# Auction System – C++ (3rd Semester DSA Project)

This project is a **console-based Auction System** developed as part of a 3rd-semester Data Structures and Algorithms (DSA) course.
It simulates a **real-time auction** using core DSA concepts such as **Binary Search Trees, Circular Queues, Linked Lists, and timer-based input handling**.

---

## Features Implemented

### 1. User Registration (BST)

* Users are stored in a **Binary Search Tree (BST)**.
* Enables **fast search** and alphabetical display of all registered users.
* Prevents duplicate registration.
* Uses **in-order traversal** to display users alphabetically.

### 2. Auction Queue (Circular Queue)

* Implements a **circular queue** using a fixed-size array and modular indexing.
* Users join the queue in **FIFO order**.
* Prevents duplicate entries in the queue.
* The queue rotates until each user has a chance to bid.
* Methods include:

  * `enqueue`
  * `isFull`
  * `isEmpty`
  * `exists` (checks if a user is already in queue)

### 3. Timed Bidding (5-Second Input Window)

* Each participant has **5 seconds to place a bid**.
* Uses:

  * `chrono` library (`steady_clock`)
  * `conio.h` (`_kbhit` and `_getch`) for non-blocking input.
* If no input is entered within the time limit, the turn is skipped automatically.

### 4. Bid Validation Logic

* Initial bid must be **greater than 0**.
* Each subsequent bid must be **strictly higher** than the current highest bid.
* Invalid bids or timeout automatically skip the user's turn.
* Only valid bids are recorded in the bid history.

### 5. Turn-Based Auction (Circular Linked List)

* Users take turns in **FIFO order** using a **circular linked list** derived from the queue.
* The auction continues until:

  * All users have had a turn, or
  * All consecutive turns result in skipped bids.

### 6. Highest Bid Tracking

* Tracks the **current highest bid** and the **username of the highest bidder**.
* Updated only on valid bids.
* Can be viewed at any time.

### 7. Bid History Tracking (Linked List)

* A **linked list** stores all accepted bids in the format:
  `username → amount`
* Full history can be displayed from the menu.

### 8. Display Functions

* Display **queue contents**
* Display **highest bid**
* Display **complete bid history**
* Display **registered user list** (alphabetical order)

---

## Data Structures and Algorithms Used

1. **Binary Search Tree (BST)**

   * Stores and searches registered users efficiently.
   * Supports alphabetical display with in-order traversal.

2. **Circular Queue (Array-Based)**

   * Manages turn order during the auction.
   * Wrap-around implemented with modular arithmetic.

3. **Linked List**

   * Stores **bid history** dynamically.
   * Supports insertion and traversal in sequential order.

4. **Circular Linked List**

   * Implements circular user rotation during the auction.

5. **Timer-Based Input**

   * Non-blocking input handled with `chrono` and `conio.h`.

6. **Basic OOP Principles**

   * Classes encapsulate **Queue**, **BST**, and **Linked List** operations.

---

## Programming Language and Libraries

* **Language:** C++
* **Standard Libraries Used:** `iostream`, `string`, `chrono`
* **Additional Library:** `conio.h` (for low-level keyboard input detection)

---

## Summary

This project demonstrates:

* Implementation of **classical data structures** (BST, circular queue, linked list)
* **Real-time input handling** with timeout
* Logical flow for an **interactive auction system**
* **Menu-driven architecture** for easy use and testing
