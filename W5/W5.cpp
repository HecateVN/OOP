#include <iostream>
#include <string>
#include <vector>
using namespace std;

// ===== Vehicle (base class) =====
class Vehicle {
protected:
    string id;
    string route;
    int capacity;
    int bookedSeats;

public:
    Vehicle(string id_, string route_, int capacity_)
        : id(id_), route(route_), capacity(capacity_), bookedSeats(0) {}

    virtual ~Vehicle() {}

    string getId() const { return id; }

    // virtual travel time
    virtual double calculateTravelTime(double distanceKm) {
        // assume normal bus speed 40 km/h
        double hours = distanceKm / 40.0;
        return hours * 60; // minutes
    }

    bool bookSeat() {
        if (bookedSeats >= capacity) {
            cout << "Vehicle " << id << " is full!\n";
            return false;
        }
        bookedSeats++;
        cout << "Booked 1 seat on " << id << ".\n";
        return true;
    }

    void displayInfo() {
        cout << "Vehicle " << id << " | Route: " << route
             << " | Capacity: " << capacity
             << " | Booked: " << bookedSeats << endl;
    }
};

// ===== ExpressBus (derived) =====
class ExpressBus : public Vehicle {
public:
    ExpressBus(string id_, string route_, int capacity_)
        : Vehicle(id_, route_, capacity_) {}

    // override travel time: 20% faster
    double calculateTravelTime(double distanceKm) override {
        double base = Vehicle::calculateTravelTime(distanceKm);
        return base * 0.8;
    }

    void displayInfo() {
        cout << "ExpressBus " << id << " | Route: " << route
             << " | Capacity: " << capacity
             << " | Booked: " << bookedSeats << endl;
    }
};

// ===== Passenger =====
class Passenger {
private:
    string name;
    string id;

public:
    Passenger(string name_, string id_) : name(name_), id(id_) {}

    string getId() const { return id; }
    string getName() const { return name; }

    void displayInfo() {
        cout << "Passenger: " << name << " (ID: " << id << ")\n";
    }
};

// ===== Station =====
class Station {
private:
    string name;
    string type; // bus or train
    vector<Vehicle*> schedules; // list of vehicles

public:
    Station(string name_, string type_) : name(name_), type(type_) {}

    void addSchedule(Vehicle* v) {
        schedules.push_back(v);
        cout << "Added vehicle " << v->getId()
             << " to station " << name << endl;
    }

    void displaySchedules() {
        cout << "Station " << name << " (" << type << ") schedules:\n";
        for (auto v : schedules) {
            v->displayInfo();
        }
    }
};

// ===== Main demo =====
int main() {
    // Create station
    Station s1("Central Bus Station", "Bus");

    // Create vehicles
    Vehicle v1("V100", "Route A", 3);
    ExpressBus e1("E200", "Express A", 2);

    // Add vehicles to station
    s1.addSchedule(&v1);
    s1.addSchedule(&e1);

    // Display schedules
    s1.displaySchedules();

    // Create passengers
    Passenger p1("Alice", "P001");
    Passenger p2("Bob", "P002");

    // Book passengers
    v1.bookSeat();
    v1.bookSeat();
    e1.bookSeat();

    // Show updated info
    cout << "\nAfter booking:\n";
    s1.displaySchedules();

    // Travel time check
    double dist = 60; // km
    cout << "\nTravel time for 60km:\n";
    cout << "Vehicle V100: " << v1.calculateTravelTime(dist) << " minutes\n";
    cout << "ExpressBus E200: " << e1.calculateTravelTime(dist) << " minutes\n";

    return 0;
}
