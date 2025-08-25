#include <iostream>
using namespace std;

class Account {
public:
    string accountNumber;
    string ownerName;
    double balance;

    void deposit(double amount) {
        balance += amount;
        cout << "Deposited: " << amount << endl;
    }

    void withdraw(double amount) {
        double minimumBalance = 100000.0;

        if (amount > balance) {
            cout << "Insufficient balance!" << endl;
        } 
        else if (balance - amount < minimumBalance) {
            cout << "Withdrawal denied! Account must keep at least " 
                 << minimumBalance << " VND." << endl;
        } 
        else {
            balance -= amount;
            cout << "Withdrew: " << amount << endl;
        }
    }

    void displayBalance() {
        cout << "Owner: " << ownerName 
             << " | Account: " << accountNumber 
             << " | Current balance: " << balance << " VND" << endl;
    }
};

int main() {
    Account acc1;
    acc1.accountNumber = "123456789";
    acc1.ownerName = "Nguyen Van A";
    acc1.balance = 200000.0;

    acc1.displayBalance();

    acc1.deposit(50000);
    acc1.displayBalance();

    acc1.withdraw(50000);
    acc1.displayBalance();

    acc1.withdraw(200000);
    acc1.displayBalance();

    return 0;
}
