#include <iostream>
using namespace std;

class Student {

    public:
        string name;
        double grade;
    
        void displayInfo() {
            cout << "Name: " << name << endl;
            cout << "Grade: " << grade << endl;
        }
    };

int main() {
    Student student1;
    student1.name = "John";
    student1.grade = 8.5;
    student1.displayInfo();
    return 0;
}