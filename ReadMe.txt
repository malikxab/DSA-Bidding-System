# Auction System – C++ (DSA Project)

This project is a console-based Auction System developed as a 3rd-semester Data Structures and Algorithms (DSA) project.
It demonstrates the use of multiple data structures and concepts including Circular Queue, Binary Search Tree, vectors, and timer-based input handling.

---

# Features

1. User Registration

   * Users register using a Binary Search Tree (BST).
   * Prevents duplicate registrations.
   * Allows displaying all registered users in sorted order.

2. Auction Queue

   * Uses a Circular Queue to manage the order of users participating in the auction.
   * Prevents a user from joining the queue more than once.
   * Queue contents can be displayed at any time.

3. Timed Bidding System

   * Each user gets 5 seconds to enter a bid.
   * If the user does not enter a bid in time, the turn is skipped.
   * Uses chrono timers and conio.h key detection.

4. Bid Validation

   * A bid is only accepted if it is greater than the current highest bid.
   * Invalid bids or late responses are skipped.

5. Highest Bid Tracking

   * Maintains the highest bid and the corresponding bidder throughout the auction.

6. Bid History

   * Stores all valid bids along with the bidder's name.
   * Supports displaying the complete bid history.

7. Auction Flow

   * Each user gets a single turn.
   * Auction ends when all users have either placed a bid or skipped.

---

# Data Structures and Concepts Used

1. Binary Search Tree (BST)

   * Used for user registration and alphabetical display of users.

2. Circular Queue

   * Used for managing the auction turn order efficiently.

3. Vector

   * Used for maintaining bid history.

4. Timer-based Input

   * Implemented using chrono and conio.h.

5. Basic OOP Concepts

   * Classes for Queue and BST.
   * Structs and global variables for managing auction state.

---

# Programming Language and Libraries

* Language: C++
* Libraries used:

  * iostream (input/output)
  * vector (dynamic array)
  * string (string handling)
  * chrono (time measurement)
  * conio.h (key detection for timed input)

---

# Project Purpose

This project was created as part of the Data Structures and Algorithms (DSA) course for 3rd semester students.
Its primary objective is to demonstrate the practical implementation of key data structures and to develop an understanding of how they can be applied in real-world systems such as an auction platform.

---

