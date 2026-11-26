# Student Apartment Rental System

CSEB3213, Group 13.

Houses are kept in a doubly linked list. Hariz wrote `linkedlist.h`. Students who are still waiting sit in the queue in `queue.h`.

## Compile

```bash
g++ -std=c++17 main.cpp -o rental
./rental
```
## Fields

ID, address, rent in RM, rooms, distance from UNITEN in km, status, landlord name.

ID, rooms, and rent have to be above 0. Distance can be 0 km. That is a house at the UNITEN gate. `getLineText` cuts spaces off both ends and will not accept a blank address or a blank landlord name.

Sort runs on a copy. Insertion sort is the elementary sort. Merge sort is the efficient sort. Linear search walks the list. Binary search by house ID sorts a copy first.
