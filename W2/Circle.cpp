#include <iostream>
#define _USE_MATH_DEFINES
#include <cmath>
#include <string>
using namespace std;

class Circle {
    public:
        double radius;
        string color;

        bool isValid() {
            return radius > 0;
        }

        double circumference() {
            return 2 * M_PI * radius;
        }

        double area() {
            return M_PI * radius * radius;
        }

        void displayColor() {
            cout << "Màu của hình tròn là: " << color << endl;
        }
};

int main() {
    Circle circle1;
    cout << "Nhập bán kính hình tròn: ";
    cin >> circle1.radius;

    cout << "Nhập màu của hình tròn: ";
    cin >> circle1.color;

    while (true) {
        if (!circle1.isValid()) {
            cout << "Bán kính không hợp lệ! Vui lòng nhập số dương." << endl;
            break;
        }

        cout << "Chu vi hình tròn: " << circle1.circumference() << endl;
        cout << "Diện tích hình tròn: " << circle1.area() << endl;
        circle1.displayColor();
        break;
    }

    return 0;
}
