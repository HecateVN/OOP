#include <iostream>
using namespace std;

class Employee {
    public:
        string name;
        double salary;
        
        void displayInfo() {
            cout << "Name: " << name << endl;
            cout << "Salary: " << salary << endl;
        }
    };

int main() {
    Employee emp1;
    emp1.name = "Alice";
    emp1.salary = 50000;
    emp1.displayInfo();
    return 0;
}