# Appointment & Resource Scheduler (C++) 🏥

This project is a sophisticated management system developed in **C++** using **Singly Linked Lists**. It focuses on handling time-based data and preventing resource allocation conflicts.

## 🧠 Key Features & Algorithms
* **Collision Detection:** A logic-heavy function that ensures no two appointments overlap by calculating end times based on duration.
* **Dynamic Time Suggestions:** The `suggestNextAvailable` function scans the linked list to find the earliest gap in a busy schedule.
* **Manual Memory Management:** Fully implements the C++ destructor logic via manual node deletion to prevent memory leaks.
* **Sorted Insertion:** Ensures the list remains chronological at all times during the `insert` operation.

## 🛠️ Tech Stack
* **Language:** C++
* **Data Structure:** Singly Linked List
* **Concepts:** Pointers, Structs, Time Calculation, Memory Management (Heap)
