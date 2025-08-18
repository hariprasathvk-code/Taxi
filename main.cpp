#include <iostream>
#include <fstream>
#include <thread>
#include <chrono>
using namespace std;

void incomingOrder(int orderId, string customerName, string bookingMethod) {
    cout << "Incoming order (" << bookingMethod << ")\n";
    ofstream f("incoming_orders.csv", ios::app);
    f << orderId << "," << customerName << "," << bookingMethod << "\n";
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

bool findTaxi() {
    ifstream f("available_taxis.csv");
    string line;
    if (getline(f, line)) {
        cout << "Taxi found\n";
        f.close();
        ifstream in("available_taxis.csv");
        ofstream t("temp.csv");
        bool removed = false;
        while (getline(in, line)) {
            if (!removed && !line.empty()) { removed = true; continue; }
            if (!line.empty()) t << line << "\n";
        }
        in.close(); t.close();
        remove("available_taxis.csv");
        rename("temp.csv", "available_taxis.csv");
        return true;
    }
    cout << "No taxi, waiting\n";
    this_thread::sleep_for(chrono::seconds(1));
    return false;
}

void assignPassenger(int orderId, string customerName) {
    cout << "Passenger assigned\n";
    ofstream h("order_history.csv", ios::app);
    h << orderId << "," << customerName << ",Assigned\n";
}

void taxiRide(int orderId, string customerName) {
    cout << "Taxi ride started\n";
    this_thread::sleep_for(chrono::seconds(1));
    ofstream h("order_history.csv", ios::app);
    h << orderId << "," << customerName << ",Completed\n";
    ofstream f("available_taxis.csv", ios::app);
    f << "Taxi_Free\n";
    cout << "Taxi ride completed\n";
}

int main() {
    int minutesToPickup = 35;
    int orderId = 1;
    string customerName, bookingMethod;

    cout << "Enter customer name: ";
    getline(cin, customerName);

    int choice;
    cout << "Booking method? (1 - Phone, 2 - Online): ";
    cin >> choice;
    cin.ignore(); // flush newline

    if (choice == 1) bookingMethod = "Phone";
    else bookingMethod = "Online";

    incomingOrder(orderId, customerName, bookingMethod);
    while (!pickupTime(minutesToPickup));
    while (!findTaxi());
    assignPassenger(orderId, customerName);
    taxiRide(orderId, customerName);

    return 0;
}
