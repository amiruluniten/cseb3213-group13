// P3 waiting list. houses are all rented, students queue here.
#ifndef WAITING_QUEUE_H
#define WAITING_QUEUE_H

#include <iostream>
#include <string>
using namespace std;

struct Student {
    int id;
    string name;
    string phone;
};

struct Node {
    Student data;
    Node* next;
};

class WaitingQueue {
private:
    Node* front;
    Node* rear;

public:
    WaitingQueue() { front = rear = NULL; }

    // drain every node on shutdown
    ~WaitingQueue() {
        Student s;
        while (dequeue(s)) {}
    }

    // true when nobody is waiting
    bool isEmpty() { return front == NULL; }

    // add at the rear. duplicate ID rejected. empty name or phone too. O(n)
    bool enqueue(Student s) {
        if (s.id <= 0 || s.name.empty() || s.phone.empty()) {
            cout << "Invalid student data.\n";
            return false;
        }
        for (Node* cur = front; cur != NULL; cur = cur->next) {
            if (cur->data.id == s.id) {
                cout << "Duplicate ID in waiting list.\n";
                return false;
            }
        }
        Node* n = new Node();
        n->data = s;
        n->next = NULL;
        if (isEmpty()) front = rear = n;
        else { rear->next = n; rear = n; }
        return true;
    }

    // take the front student off. O(1)
    bool dequeue(Student& s) {
        if (isEmpty()) return false;
        Node* temp = front;
        s = temp->data;
        front = front->next;
        if (front == NULL) rear = NULL;
        delete temp;
        return true;
    }

    // who is next. does not remove them. O(1)
    bool peek(Student& s) {
        if (isEmpty()) return false;
        s = front->data;
        return true;
    }

    // print front to rear.
    void display() {
        if (isEmpty()) { cout << "Waiting list is empty.\n"; return; }
        for (Node* cur = front; cur != NULL; cur = cur->next)
            cout << cur->data.id << " | " << cur->data.name
                 << " | " << cur->data.phone << "\n";
    }
};

#endif
