#include <iostream>
using namespace std;

class Person {
public:
    string name;
    int age;
    string address;
    string phoneNumber; // thêm số điện thoại

    void displayInfo() {
        cout << "Name: " << name << endl;
        cout << "Age: " << age << endl;
        cout << "Address: " << address << endl;
        cout << "Phone Number: " << phoneNumber << endl;
    }

    bool isAdult() {
        return age >= 18;
    }

    void move(string newAddress) {
        address = newAddress;
        cout << "Address updated to: " << address << endl;
    }

    void greet() {
        cout << "Hello, my name is " << name << "." << endl;
    }
};

int main() {
    Person person1;
    person1.name = "John Doe";
    person1.age = 20;
    person1.address = "123 Main St";
    person1.phoneNumber = "0123456789";

    person1.displayInfo();

    if (person1.isAdult()) {
        cout << "This person is an adult." << endl;
    } else {
        cout << "This person is not an adult." << endl;
    }

    // Thử cập nhật địa chỉ
    person1.move("456 New Street");

    // Thử lời chào
    person1.greet();

    return 0;
}
