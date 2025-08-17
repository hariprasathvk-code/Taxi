#include <iostream>
#include <thread>
#include <chrono>
using namespace std;

void incomingOrder() {
    cout << "Incoming order\n";
}


int main() {
    int minutesToPickup = 35;
    int availableTaxis = 1;

    incomingOrder();
    while (!pickupTime(minutesToPickup));
    while (!findTaxi(availableTaxis));
    assignPassenger();
    taxiRide(availableTaxis);

    return 0;
}
