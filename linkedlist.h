#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include "house.h"

// Hariz. prev is NULL at the head, next is NULL at the tail.
class HouseNode {
public:
    House data;
    HouseNode *next, *prev;
};

HouseNode *createHouseNode(House h) {
    HouseNode *n = new HouseNode();
    n->data = h;
    n->next = n->prev = NULL;
    return n;
}

// add at the tail. duplicate ID rejected. O(n)
bool addHouse(HouseNode *&head, HouseNode *&tail, House h) {
    HouseNode *p = head;
    while (p != NULL) {
        if (p->data.id == h.id) {
            cout << "Error: House ID already exists!\n";
            return false;
        }
        p = p->next;
    }
    HouseNode *n = createHouseNode(h);
    if (head == NULL) {
        head = tail = n;
    } else {
        tail->next = n;
        n->prev = tail;
        tail = n;
    }
    return true;
}

// print every house.
void displayAll(HouseNode *p) {
    if (p == NULL) {
        cout << "No house listings found.\n";
        return;
    }
    cout << "\n--- All House Listings ---\n";
    while (p != NULL) {
        cout << "ID: " << p->data.id
             << " | Address: " << p->data.address
             << " | Rent: RM" << p->data.rent
             << " | Status: " << p->data.status << endl;
        p = p->next;
    }
}

// delete by ID. head is separate because head has to move. O(n)
bool removeHouse(HouseNode *&head, HouseNode *&tail, int keyId) {
    if (head == NULL) {
        cout << "The list is empty.\n";
        return false;
    }

    HouseNode *n = head;

    // head node
    if (head->data.id == keyId) {
        head = head->next;
        if (head != NULL) {
            head->prev = NULL;
        } else {
            tail = NULL;
        }
        delete n;
        cout << "House listing removed successfully.\n";
        return true;
    }

    // middle or tail node
    while (n != NULL && n->data.id != keyId) {
        n = n->next;
    }

    if (n == NULL) {
        cout << "House ID not found.\n";
        return false;
    }

    if (n->prev != NULL)
        n->prev->next = n->next;

    if (n->next != NULL)
        n->next->prev = n->prev;
    else
        tail = n->prev;

    delete n;
    cout << "House listing removed successfully.\n";
    return true;
}

// Available only, then the totals. "available" still matches old records.
void displayAvailable(HouseNode *p) {
    int totalAvailable = 0, totalRented = 0;

    if (p == NULL) {
        cout << "The list is empty.\n";
        return;
    }

    cout << "\n--- Available House Listings ---\n\n";
    while (p != NULL) {
        if (p->data.status == "Available" || p->data.status == "available") {
            cout << "ID: " << p->data.id
                 << " | Address: " << p->data.address
                 << " | Rent: RM" << p->data.rent
                 << " | Rooms: " << p->data.rooms
                 << " | Landlord: " << p->data.landlordName
                 << " : Available\n";
            totalAvailable++;
        } else {
            totalRented++;
        }
        p = p->next;
    }

    cout << "\nTotal Available: " << totalAvailable << endl;
    cout << "Total Rented: " << totalRented << endl;
    cout << "Total Listings: " << (totalAvailable + totalRented) << endl;
    cout << endl;
}

// find the ID and replace the record. O(n)
bool updateHouse(HouseNode *head, House edited) {
    if (head == NULL) {
        cout << "The list is empty.\n";
        return false;
    }

    HouseNode *p = head;
    while (p != NULL && p->data.id != edited.id) {
        p = p->next;
    }

    if (p == NULL) {
        cout << "House ID " << edited.id << " not found.\n";
        return false;
    }

    p->data = edited;

    cout << "House listing ID " << edited.id << " updated successfully!\n";
    return true;
}

#endif
