#ifndef SEARCHING_H
#define SEARCHING_H

#include <iostream>
#include <string>

#include "house.h"
#include "linkedlist.h"
#include "sorting.h"

using namespace std;

// 1 = address, 2 = landlord. prints every match, not just the first. O(n)
void linearSearch(HouseNode *head, string key, int field) {
    HouseNode *cur = head;

    if (cur == NULL) {
        cout << "The house list is empty.\n";
        return;
    }
    if (field != 1 && field != 2) {
        cout << "Invalid search field.\n";
        return;
    }

    bool found = false;
    int position = 0;

    while (cur != NULL) {
        position++;
        House &h = cur->data;

        bool match = (field == 1) ? (h.address == key) : (h.landlordName == key);

        if (match) {
            found = true;
            cout << "Match at list position " << position << ":\n";
            printHouse(h);
        }
        cur = cur->next;
    }

    if (!found) {
        cout << "No house found for that " << (field == 1 ? "address" : "landlord name") << ".\n";
    }
}

// copy into arr[], sort by ID, then LOW / HI / MID. O(n log n), then O(log n)
void searchById(HouseNode *head, int id) {
    HouseNode *cur = head;

    if (cur == NULL) {
        cout << "The house list is empty.\n";
        return;
    }

    House arr[MAX_HOUSE];
    int n = 0;
    while (cur != NULL && n < MAX_HOUSE) {
        arr[n] = cur->data;
        n++;
        cur = cur->next;
    }

    // Adam. merge sort, ID, ascending.
    sortHouses(arr, n, 2, 3, 1);

    int LOW = 0;
    int HI = n - 1;
    bool found = false;

    while (LOW <= HI) {
        int MID = (LOW + HI) / 2;

        if (arr[MID].id == id) {
            found = true;
            cout << "Found at sorted-copy index " << MID << ":\n";
            printHouse(arr[MID]);
            break;
        }
        else if (arr[MID].id < id) {
            LOW = MID + 1;
        }
        else {
            HI = MID - 1;
        }
    }

    if (!found) {
        cout << "No house found with ID " << id << ".\n";
    }
}

#endif
