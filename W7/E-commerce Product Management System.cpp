#include <iostream>
#include <string>
#include <vector>
using namespace std;

// ======================== INTERFACE: Discountable ==========================
// Abstract interface: all subclasses must implement applyDiscount()
class Discountable {
public:
    virtual double applyDiscount(double rate) = 0;
    virtual ~Discountable() {}
};

// ======================== BASE CLASS: Product ==============================
class Product : public Discountable {
private:
    string id;
    string name;
    double price;
    int stock;

public:
    // Constructor
    Product(string pid, string pname, double pprice, int pstock) {
        id = pid;
        name = pname;
        price = pprice;
        stock = pstock;
    }

    // Getters
    string getId() { return id; }
    string getName() { return name; }
    double getPrice() { return price; }
    int getStock() { return stock; }

    // Update stock
    virtual void updateStock(int quantity) {
        if (stock + quantity >= 0) {
            stock += quantity;
        } else {
            cout << "Not enough stock for " << name << endl;
        }
    }

    // Display product info
    virtual void display() {
        cout << "Product [" << id << "] " << name 
             << " - $" << price 
             << " | Stock: " << stock << endl;
    }

    // Implement discount interface
    double applyDiscount(double rate) override {
        return price * (1 - rate);
    }

    // Overload == (compare by id)
    bool operator==(Product& other) {
        return id == other.id;
    }
};

// ======================== DERIVED CLASSES =================================
class Electronics : public Product {
private:
    int warranty;

public:
    Electronics(string id, string name, double price, int stock, int w)
        : Product(id, name, price, stock), warranty(w) {}

    void display() override {
        cout << "Electronics [" << getId() << "] " << getName()
             << " - $" << getPrice()
             << " | Stock: " << getStock()
             << " | Warranty: " << warranty << " months" << endl;
    }

    void updateStock(int quantity) override {
        cout << "(Fragile handling for electronics)\n";
        Product::updateStock(quantity);
    }
};

class Clothing : public Product {
private:
    string size;

public:
    Clothing(string id, string name, double price, int stock, string s)
        : Product(id, name, price, stock), size(s) {}

    void display() override {
        cout << "Clothing [" << getId() << "] " << getName()
             << " - $" << getPrice()
             << " | Stock: " << getStock()
             << " | Size: " << size << endl;
    }
};

// ======================== TEMPLATE CLASS: InventoryList ====================
template <typename T>
class InventoryList {
private:
    vector<T> items;

public:
    void add(T item) {
        items.push_back(item);
    }

    T get(int index) {
        return items[index];
    }

    void displayAll() {
        for (auto item : items) {
            item->display();
        }
    }
};

// ======================== CLASS: ShoppingCart ==============================
class ShoppingCart : public Discountable {
private:
    vector<Product*> cart;
    double total = 0;

public:
    // Overload += to add product to cart
    ShoppingCart& operator+=(Product* p) {
        if (p->getStock() > 0) {
            cart.push_back(p);
            total += p->getPrice();
            p->updateStock(-1);
        } else {
            cout << "Cannot add " << p->getName() << " (out of stock)" << endl;
        }
        return *this;
    }

    void display() {
        cout << "=== Cart Contents ===" << endl;
        for (auto p : cart) {
            p->display();
        }
        cout << "Total: $" << total << endl;
    }

    double applyDiscount(double rate) override {
        total = total * (1 - rate);
        return total;
    }
};

// ======================== CLASS: Order ====================================
class Order {
private:
    string orderId;
    ShoppingCart cart;

public:
    Order(string id, ShoppingCart c) {
        orderId = id;
        cart = c;
    }

    void display() {
        cout << "\n=== Order " << orderId << " ===" << endl;
        cart.display();
    }
};

// ======================== MAIN ============================================
int main() {
    // Create products
    Product book("P01", "C++ Book", 15.0, 5);
    Electronics laptop("E01", "Laptop", 1200.0, 2, 24);
    Clothing tshirt("C01", "T-Shirt", 20.0, 3, "L");

    // Inventory
    InventoryList<Product*> inventory;
    inventory.add(&book);
    inventory.add(&laptop);
    inventory.add(&tshirt);

    cout << "--- INVENTORY ---" << endl;
    inventory.displayAll();

    // Cart
    ShoppingCart cart;
    cart += &book;
    cart += &laptop;
    cart += &tshirt;
    cart += &laptop; // laptop lần 2
    cart += &laptop; // hết stock

    cout << "\n--- CART BEFORE DISCOUNT ---" << endl;
    cart.display();

    cout << "\nApplying 10% discount..." << endl;
    cart.applyDiscount(0.1);
    cart.display();

    // Compare products
    cout << "\nCompare book and laptop: " 
         << ((book == laptop) ? "same" : "different") << endl;

    // Order
    Order order1("O001", cart);
    order1.display();

    return 0;
}
