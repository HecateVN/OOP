// Generated with help from ChatGPT & copilot
#include <iostream>
#include <string>
#include <vector>
#include <limits>
using namespace std;

class Vehicle {
private:
    string brand;
    string type;
    int maxSpeed;
    string fuelType;

public:
    // Constructor
    Vehicle(string b, string t, int speed, string fuel) {
        brand = b;
        type = t;
        maxSpeed = speed;
        fuelType = fuel;
    }

    // Methods

    void showInfo(int index = -1) const {
    if (index >= 0)
        cout << index + 1 << ".  Brand: " << brand
             << "\n   Type: " << type
             << "\n   Max Speed: " << maxSpeed << " km/h"
             << "\n   Fuel Type: " << fuelType
             << "\n==========================================" << endl;
    }

    string getBrand() {
        return brand;
    }

    string getType() {
        return type;
    }

    int getMaxSpeed() {
        return maxSpeed;
    }

    string getFuelType() {
        return fuelType;
    }
};

class VehicleManager {
private:
    vector<Vehicle>& vehicles;
public:
    //  Constructor
    VehicleManager(vector<Vehicle>& v) : vehicles(v) {}
    
    // Methods
    void showVehicles() {
        cout << "\nVehicles:\n";
        for (size_t i = 0; i < vehicles.size(); ++i) {
            vehicles[i].showInfo(i);
        }
    }

    Vehicle addVehicle() {
        string brand, type, fuel;
        int speed;

        // --- Brand ---
        do {
            cout << "Enter vehicle brand: ";
            getline(cin, brand);
            if (brand.empty()) {
                cout << "Brand cannot be empty. Try again.\n";
            }
        } while (brand.empty());

        // --- Type ---
        do {
            cout << "Enter vehicle type: ";
            getline(cin, type);
            if (type.empty()) {
                cout << "Type cannot be empty. Try again.\n";
            }
        } while (type.empty());

        // --- Speed ---
        while (true) {
            cout << "Enter max speed (km/h): ";
            if (cin >> speed) {
                if (speed > 0 && speed <= 500) {
                    break; // valid
                } else {
                    cout << "Speed must be between 1 and 500 km/h.\n";
                }
            } else {
                cout << "Invalid input. Please enter a number.\n";
                cin.clear(); // clear error flag
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // discard bad input
            }
        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // clear leftover newline

        // --- Fuel ---
        do {
            cout << "Enter fuel type (e.g., Petrol, Diesel, Electric): ";
            getline(cin, fuel);
            if (fuel.empty()) {
                cout << "Fuel type cannot be empty. Try again.\n";
            }
        } while (fuel.empty());

        return Vehicle(brand, type, speed, fuel);
    }


    void deleteVehicle() {
        if (vehicles.empty()) {
            cout << "No vehicles to edit.\n";
            return;
        }

        // 1. Show all vehicles before choosing
        cout << "\nCurrent Vehicles:\n";
        showVehicles();

        // 2. Ask which vehicle to delete
        int idx;
        cout << "Enter vehicle number to delete: ";
        cin >> idx;
        if (idx >= 1 && idx <= vehicles.size()) {
            vehicles.erase(vehicles.begin() + (idx - 1));
            cout << "Vehicle deleted.\n";
        } else {
            cout << "Invalid number.\n";
        }
    }

    void editVehicle() {
        if (vehicles.empty()) {
            cout << "No vehicles to edit.\n";
            return;
        }

        // 1. Show all vehicles before choosing
        cout << "\nCurrent Vehicles:\n";
        showVehicles();

        // 2. Ask which vehicle to edit
        int idx;
        cout << "Enter vehicle number to edit: ";
        while (!(cin >> idx) || idx < 1 || idx > (int)vehicles.size()) {
            cout << "Invalid number. Try again: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // clear newline

        // 3. Update the vehicle
        vehicles[idx - 1] = addVehicle();
        cout << "Vehicle updated successfully.\n";
    }

};

int main() {
    system(" color 0A");

    // Create a list of objects
    vector<Vehicle> vehicles = {
        Vehicle("Toyota", "Car", 200, "Petrol"),
        Vehicle("Volvo", "Truck", 150, "Diesel"),
        Vehicle("Honda", "Motorcycle", 180, "Petrol")
    };

    VehicleManager manager(vehicles);

    int choice;
    do {
        cout << "============================" << endl;
        cout << "          Menu\n";
        cout << "1. Show all vehicles\n";
        cout << "2. Add a vehicle\n";
        cout << "3. Delete a vehicle\n";
        cout << "4. Edit a vehicle\n";
        cout << "0. Exit\n";
        cout << "============================" << endl;
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear input buffer

        switch (choice) {
            case 1:
                manager.showVehicles();
                break;
            case 2: {
                Vehicle newVehicle = manager.addVehicle();
                vehicles.push_back(newVehicle);
                cout << "Vehicle added successfully.\n";
                break;
            }
            case 3:
                manager.deleteVehicle();
                break;
            case 4:
                manager.editVehicle();
                break;
            case 0:
                cout << "Exiting...\n";
                break;
            default:
                cout << "Invalid choice.\n";
        }

        if (choice != 0) {
            cout << "\nPress Enter to show the menu...";
            cin.get();
            system("cls"); // Clear the screen after pressing Enter
        }
    } while (choice != 0);

    return 0;
}
