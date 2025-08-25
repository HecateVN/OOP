#include <iostream>
using namespace std;

class Laptop {
public:
    string brand;
    string model;
    int ram;
    int storage;

    void displayInfo() {
        cout << "Brand: " << brand << endl;
        cout << "Model: " << model << endl;
        cout << "RAM: " << ram << " GB" << endl;
        cout << "Storage: " << storage << " GB" << endl;
    }

    void checkRAM(int requiredRAM) {
        if (ram >= requiredRAM) {
            cout << "This laptop has enough RAM to run the software." << endl;
        } else {
            cout << "This laptop does not have enough RAM to run the software." << endl;
        }
    }

    void upgradeRAM(int additionalRAM) {
        ram += additionalRAM;
        cout << "RAM upgraded by " << additionalRAM << " GB." << endl;
        cout << "New RAM size: " << ram << " GB." << endl;
    }
};

int main() {
    Laptop laptop1;
    laptop1.brand = "Dell";
    laptop1.model = "XPS 13";
    laptop1.ram = 8;
    laptop1.storage = 256;

    laptop1.displayInfo();

    // Kiểm tra RAM
    laptop1.checkRAM(16);

    // Nâng cấp RAM thêm 8GB
    laptop1.upgradeRAM(8);

    laptop1.displayInfo();

    return 0;
}
