#include <iostream>
#include <thread>
#include <chrono>
using namespace std;

void incomingOrder() {
    cout << "Incoming order\n";
}

bool pickupTime(int &minutesToPickup) {
    if (minutesToPickup <= 30) {
        cout << "Pickup within 30 minutes\n";
        return true;
    } else {
        cout << "Waiting for pickup time\n";
        this_thread::sleep_for(chrono::seconds(1));
        minutesToPickup--;
        return false;
    }
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
