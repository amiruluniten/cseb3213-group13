// CSEB3213 Group 13
// Student Apartment Rental System

#include "linkedlist.h"
#include "queue.h"
#include "sorting.h"
#include "searching.h"

// bad input asks again. program should not crash.

// read an int. Ctrl-D returns -1 and leaves eof set.
// a typed -1 is also -1, so exit only when eof is set.
int getIntInput(string prompt) {
    int x;
    while (true) {
        cout << prompt;
        cin >> x;
        if (cin.fail()) {
            if (cin.eof()) {
                cout << "\nEnd of program\n";
                return -1;
            }
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Invalid input. Enter a number.\n";
        } else {
            cin.ignore(1000, '\n');
            return x;
        }
    }
}

// same loop, for double.
double getDoubleInput(string prompt) {
    double x;
    while (true) {
        cout << prompt;
        cin >> x;
        if (cin.fail()) {
            if (cin.eof()) {
                cout << "\nEnd of program\n";
                return -1;
            }
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Invalid input. Enter a number.\n";
        } else {
            cin.ignore(1000, '\n');
            return x;
        }
    }
}

// getline, then cut spaces at both ends. blank line is rejected.
string getLineText(string prompt) {
    string s;
    while (true) {
        cout << prompt;
        if (!getline(cin, s)) {
            cout << "\nEnd of program\n";
            return "";
        }
        while (s.size() > 0 && s[0] == ' ') {
            s.erase(0, 1);
        }
        while (s.size() > 0 && s[s.size() - 1] == ' ') {
            s.erase(s.size() - 1, 1);
        }
        if (s == "") {
            cout << "Input cannot be empty.\n";
        } else {
            return s;
        }
    }
}

// house ID, rooms, student ID. 0 and below are rejected.
int getPosInt(string prompt) {
    while (true) {
        int x = getIntInput(prompt);
        if (cin.eof()) {
            return -1;
        }
        if (x <= 0) {
            cout << "Enter a number greater than 0.\n";
        } else {
            return x;
        }
    }
}

// allowZero is only for distance. a house at the UNITEN gate is 0 km.
// rent cannot be 0.
double getAmount(string prompt, bool allowZero) {
    while (true) {
        double x = getDoubleInput(prompt);
        if (cin.eof()) {
            return -1;
        }
        bool ok = (x > 0) || (allowZero && x == 0);
        if (ok) {
            return x;
        }
        if (allowZero) {
            cout << "Distance cannot be negative.\n";
        } else {
            cout << "Enter a number greater than 0.\n";
        }
    }
}

// 1 or 2. typing the word broke the Available filter ("available", typos).
string getRentalStatus() {
    while (true) {
        int c = getIntInput("Status (1 = Available, 2 = Rented): ");
        if (cin.eof()) {
            return "";
        }
        if (c == 1) {
            return "Available";
        }
        if (c == 2) {
            return "Rented";
        }
        cout << "Invalid status. Enter 1 or 2.\n";
    }
}

// Hariz's list. find by ID. O(n)
HouseNode *findHouseById(HouseNode *head, int id) {
    HouseNode *p = head;
    while (p != NULL) {
        if (p->data.id == id) {
            return p;
        }
        p = p->next;
    }
    return NULL;
}

// lab 4: next one way, prev the other.
void traverse(HouseNode *head, HouseNode *tail) {
    if (head == NULL) {
        cout << "The list is empty.\n";
        return;
    }
    cout << "\n--- Forward (head to tail) ---\n";
    for (HouseNode *p = head; p != NULL; p = p->next) {
        printHouse(p->data);
    }
    cout << "\n--- Backward (tail to head) ---\n";
    for (HouseNode *p = tail; p != NULL; p = p->prev) {
        printHouse(p->data);
    }
}

// free every HouseNode. called once before return.
void deleteWholeList(HouseNode *&head, HouseNode *&tail) {
    while (head != NULL) {
        HouseNode *next = head->next;
        delete head;
        head = next;
    }
    tail = NULL;
}

// P3 rule. Available house goes to whoever queued first.
void offerToNextInLine(HouseNode *house, WaitingQueue &wait) {
    Student s;
    if (!wait.dequeue(s)) {
        return;
    }
    house->data.status = "Rented";
    cout << "House " << house->data.id << " offered to " << s.name
         << " (student ID " << s.id << ", " << s.phone << "). Status is Rented.\n";
}

// first Available from head. NULL if none.
HouseNode *findVacantHouse(HouseNode *head) {
    for (HouseNode *p = head; p != NULL; p = p->next) {
        if (p->data.status == "Available") {
            return p;
        }
    }
    return NULL;
}

void printMenu() {
    cout << "\n==== Student Apartment Rental ====\n";
    cout << "1  Add house\n";
    cout << "2  Update house\n";
    cout << "3  Remove house\n";
    cout << "4  Display all houses\n";
    cout << "5  Display available houses\n";
    cout << "6  Traverse list (forward and backward)\n";
    cout << "7  Sort houses (copy only)\n";
    cout << "8  Search by address or landlord\n";
    cout << "9  Search by house ID (binary search)\n";
    cout << "10 Add student to waiting list\n";
    cout << "11 Display waiting list\n";
    cout << "12 Exit\n";
}

// demo data. all rented, so option 10 has a queue to hand a house to.
void loadSampleData(HouseNode *&head, HouseNode *&tail, WaitingQueue &wait) {
    House h;
    Student s;

    h.id = 101;
    h.address = "Jalan Kajang 3";
    h.rent = 450;
    h.rooms = 1;
    h.distanceKm = 1.2;
    h.status = "Rented";
    h.landlordName = "Ahmad";
    addHouse(head, tail, h);

    h.id = 102;
    h.address = "Taman Kajang Utama";
    h.rent = 700;
    h.rooms = 2;
    h.distanceKm = 2.5;
    h.status = "Rented";
    h.landlordName = "Siew May";
    addHouse(head, tail, h);

    h.id = 103;
    h.address = "Bandar Baru Bangi";
    h.rent = 550;
    h.rooms = 1;
    h.distanceKm = 4.0;
    h.status = "Rented";
    h.landlordName = "Ravi";
    addHouse(head, tail, h);

    h.id = 104;
    h.address = "Kajang Avenue";
    h.rent = 900;
    h.rooms = 3;
    h.distanceKm = 1.8;
    h.status = "Rented";
    h.landlordName = "John";
    addHouse(head, tail, h);

    h.id = 105;
    h.address = "Seksyen 7 Bangi";
    h.rent = 650;
    h.rooms = 2;
    h.distanceKm = 5.5;
    h.status = "Rented";
    h.landlordName = "Mohammad";
    addHouse(head, tail, h);

    h.id = 106;
    h.address = "Taman Jasmin";
    h.rent = 500;
    h.rooms = 1;
    h.distanceKm = 3.2;
    h.status = "Rented";
    h.landlordName = "Jennifer";
    addHouse(head, tail, h);

    s.id = 201;
    s.name = "Ali";
    s.phone = "012-3451111";
    wait.enqueue(s);

    s.id = 202;
    s.name = "Siti";
    s.phone = "013-3452222";
    wait.enqueue(s);

    s.id = 203;
    s.name = "Kumar";
    s.phone = "014-3453333";
    wait.enqueue(s);

    cout << "Sample data loaded: 6 houses, all Rented. 3 students waiting.\n";
}

// one house form. Ctrl-D halfway just returns. nothing is saved.
void addNewListing(HouseNode *&head, HouseNode *&tail, WaitingQueue &wait) {
    House h;
    h.id = getPosInt("House ID: ");
    if (cin.eof()) return;

    // stop here if this ID is already in the list.
    if (findHouseById(head, h.id) != NULL) {
        cout << "Error: House ID already exists!\n";
        return;
    }

    h.address = getLineText("Address: ");
    h.rent = getAmount("Rent (RM): ", false);
    h.rooms = getPosInt("Rooms: ");
    h.distanceKm = getAmount("Distance from UNITEN (km): ", true);
    h.status = getRentalStatus();
    h.landlordName = getLineText("Landlord name: ");
    if (cin.eof()) return;

    if (!addHouse(head, tail, h)) {
        return;
    }
    cout << "House listing added successfully.\n";

    // someone already waiting? give them this house.
    if (h.status == "Available") {
        offerToNextInLine(tail, wait);
    }
}

// edit one field. old record stays if the new value fails.
void updateListing(HouseNode *head, WaitingQueue &wait) {
    if (head == NULL) {
        cout << "The list is empty.\n";
        return;
    }
    int id = getPosInt("House ID to update: ");
    if (cin.eof()) return;
    HouseNode *n = findHouseById(head, id);
    if (n == NULL) {
        cout << "House ID " << id << " not found.\n";
        return;
    }
    cout << "Current record:\n";
    printHouse(n->data);

    cout << "1 Address\n2 Rent\n3 Rooms\n4 Distance\n5 Status\n6 Landlord name\n";
    int field = getIntInput("Field: ");
    if (cin.eof()) return;

    string oldStatus = n->data.status;
    House edited = n->data;
    switch (field) {
        case 1:
            edited.address = getLineText("New address: ");
            break;
        case 2:
            edited.rent = getAmount("New rent (RM): ", false);
            break;
        case 3:
            edited.rooms = getPosInt("New rooms: ");
            break;
        case 4:
            edited.distanceKm = getAmount("New distance (km): ", true);
            break;
        case 5:
            edited.status = getRentalStatus();
            break;
        case 6:
            edited.landlordName = getLineText("New landlord name: ");
            break;
        default:
            cout << "Invalid field.\n";
            return;
    }
    if (cin.eof()) return;

    if (!updateHouse(head, edited)) {
        return;
    }
    // status just became Available. same handover as a new listing.
    if (oldStatus != "Available" && n->data.status == "Available") {
        offerToNextInLine(n, wait);
    }
}

// print the list first. demo reads the ID off that.
void removeListing(HouseNode *&head, HouseNode *&tail) {
    if (head == NULL) {
        cout << "The list is empty.\n";
        return;
    }
    displayAll(head);
    int id = getPosInt("\nEnter House ID to remove: ");
    if (cin.eof()) return;
    removeHouse(head, tail, id);
}

// sort a copy. list stays in the order houses were added.
void showSortedCopy(HouseNode *head) {
    if (head == NULL) {
        cout << "The list is empty. Nothing to sort.\n";
        return;
    }
    cout << "1 Insertion sort by rent\n";
    cout << "2 Insertion sort by distance\n";
    cout << "3 Merge sort by rent\n";
    cout << "4 Merge sort by distance\n";
    cout << "5 Merge sort by house ID\n";
    int pick = getIntInput("Sort: ");
    if (pick < 1 || pick > 5) {
        cout << "Invalid sort choice.\n";
        return;
    }
    int order = getIntInput("Order (1 = ascending, 2 = descending): ");
    if (order != 1 && order != 2) {
        cout << "Invalid order.\n";
        return;
    }
    // 1-2 insertion, 3-5 merge (Adam). key 1 rent, 2 distance, 3 id.
    int method = (pick <= 2) ? 1 : 2;
    int keyType = (pick == 1 || pick == 3) ? 1 : (pick == 2 || pick == 4) ? 2 : 3;

    House arr[MAX_HOUSE];
    int n = 0;
    for (HouseNode *p = head; p != NULL && n < MAX_HOUSE; p = p->next) {
        arr[n] = p->data;
        n++;
    }
    sortHouses(arr, n, method, keyType, order);

    cout << "Sorted copy. Original list is not changed.\n";
    for (int i = 0; i < n; i++) {
        printHouse(arr[i]);
    }
}

// exact match. contains-match pulled in too many streets.
void searchAddressOrLandlord(HouseNode *head) {
    int field = getIntInput("Search by (1 = address, 2 = landlord): ");
    if (cin.eof()) return;
    if (field != 1 && field != 2) {
        cout << "Invalid field.\n";
        return;
    }
    string key = getLineText(field == 1 ? "Exact address: " : "Exact landlord name: ");
    if (cin.eof()) return;
    linearSearch(head, key, field);
}

// searching.h sorts a copy by ID first. list order unchanged.
void searchByIdBinary(HouseNode *head) {
    int id = getPosInt("House ID: ");
    if (cin.eof()) return;
    searchById(head, id);
}

// after they join, hand over a house that was already Available.
void joinWaitingList(HouseNode *head, WaitingQueue &wait) {
    Student s;
    s.id = getPosInt("Student ID: ");
    if (cin.eof()) return;
    s.name = getLineText("Student name: ");
    if (cin.eof()) return;
    s.phone = getLineText("Phone: ");
    if (cin.eof()) return;

    if (!wait.enqueue(s)) {
        cout << "Student not added to the waiting list.\n";
        return;
    }
    cout << "Student added to the waiting list.\n";

    HouseNode *vacant = findVacantHouse(head);
    if (vacant != NULL) {
        offerToNextInLine(vacant, wait);
    }
}

void showWaitingList(WaitingQueue &wait) {
    cout << "\n--- Waiting List (front to rear) ---\n";
    wait.display();
    Student s;
    if (wait.peek(s)) {
        cout << "Next in line (peek): " << s.name << " (ID " << s.id << ")\n";
    }
}

int main() {
    HouseNode *head = NULL, *tail = NULL;
    WaitingQueue wait;

    loadSampleData(head, tail, wait);

    int choice;
    do {
        printMenu();
        choice = getIntInput("Choice: ");
        if (choice == -1 && cin.eof()) {
            // Ctrl-D. a typed -1 falls through as an invalid choice.
            break;
        }
        switch (choice) {
            case 1: addNewListing(head, tail, wait); break;
            case 2: updateListing(head, wait); break;
            case 3: removeListing(head, tail); break;
            case 4: displayAll(head); break;
            case 5: displayAvailable(head); break;
            case 6: traverse(head, tail); break;
            case 7: showSortedCopy(head); break;
            case 8: searchAddressOrLandlord(head); break;
            case 9: searchByIdBinary(head); break;
            case 10: joinWaitingList(head, wait); break;
            case 11: showWaitingList(wait); break;
            case 12: cout << "End of program\n"; break;
            default: cout << "Invalid menu choice.\n";
        }
    } while (choice != 12);

    deleteWholeList(head, tail);
    return 0;
}
