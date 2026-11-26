#ifndef HOUSE_H
#define HOUSE_H

#include <iostream>
#include <string>
using namespace std;

struct House {
    int id;
    string address;
    double rent;
    int rooms;
    double distanceKm;
    string status;
    string landlordName;
};

const int MAX_HOUSE = 100;

// one house, one line.
void printHouse(House h) {
    cout << "ID: " << h.id
         << " | " << h.address
         << " | RM" << h.rent
         << " | Rooms: " << h.rooms
         << " | " << h.distanceKm << " km"
         << " | " << h.status
         << " | Landlord: " << h.landlordName << endl;
}

#endif
