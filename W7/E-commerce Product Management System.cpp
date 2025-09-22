#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
using namespace std;

// ======================== INTERFACE: Discountable ==========================
// Abstract interface: bất cứ lớp nào kế thừa đều phải cài đặt applyDiscount
class Discountable {
public:
    virtual double applyDiscount(double rate) = 0;
    virtual ~Discountable() = default;
};

// ======================== BASE CLASS: Product ==========================
class Product : public Discountable {
private:
    string id;
    string name;
    double price;
    int stock;

public:
    Product(const string& id, const string& name, double price, int stock)
        : id(id), name(name), price(price), stock(stock) {}

    virtual ~Product() = default;

    // Getter / Setter
    string getId() const { return id; }
    string getName() const { return name; }
    double getPrice() const { return price; }
    int getStock() const { return stock; }
    void setPrice(double p) { price = p; }
    void setStock(int s) { stock = s; }

    // Display (virtual for polymorphism)
    virtual void display() const {
        cout << "Product [" << id << "] " << name
             << " - $" << fixed << setprecision(2) << price
             << " | Stock: " << stock << '\n';
    }

    // Update stock (can be overridden)
    virtual void updateStock(int quantity) {
        if (stock + quantity < 0) {
            cout << "Not enough stock of " << name << " to remove " << -quantity << " units.\n";
        } else {
            stock += quantity;
        }
    }

    // Implement Discountable
    double applyDiscount(double rate) override {
        if (rate < 0.0 || rate > 1.0) {
            cout << "Invalid discount rate. No change.\n";
            return price;
        }
        double discounted = price * (1.0 - rate);
        return discounted;
    }

    // Overload == to compare by ID
    bool operator==(const Product& other) const {
        return this->id == other.id;
    }
};

// ======================== DERIVED CLASSES ==========================
// Electronics derived from Product
class Electronics : public Product {
private:
    int warrantyMonths;

public:
    Electronics(const string& id, const string& name, double price, int stock, int warranty)
        : Product(id, name, price, stock), warrantyMonths(warranty) {}

    void display() const override {
        cout << "Electronics [" << getId() << "] " << getName()
             << " - $" << fixed << setprecision(2) << getPrice()
             << " | Stock: " << getStock()
             << " | Warranty: " << warrantyMonths << " months\n";
    }

    void updateStock(int quantity) override {
        cout << "(Electronics stock update: handle fragile packaging)\n";
        Product::updateStock(quantity);
    }
};

// Clothing derived from Product
class Clothing : public Product {
private:
    string size;

public:
    Clothing(const string& id, const string& name, double price, int stock, const string& size)
        : Product(id, name, price, stock), size(size) {}

    void display() const override {
        cout << "Clothing [" << getId() << "] " << getName()
             << " - $" << fixed << setprecision(2) << getPrice()
             << " | Stock: " << getStock()
             << " | Size: " << size << '\n';
    }
};

// ======================== TEMPLATE CLASS: InventoryList ==========================
// Generic container for items of type T
template <typename T>
class InventoryList {
private:
    vector<T> items;

public:
    void add(const T& item) {
        items.push_back(item);
    }

    void removeAt(int index) {
        if (index >= 0 && index < (int)items.size())
            items.erase(items.begin() + index);
        else
            throw out_of_range("Invalid index in removeAt");
    }

    int size() const { return static_cast<int>(items.size()); }

    T& get(int index) {
        if (index < 0 || index >= (int)items.size())
            throw out_of_range("Invalid index in get");
        return items[index];
    }

    const T& get(int index) const {
        if (index < 0 || index >= (int)items.size())
            throw out_of_range("Invalid index in get const");
        return items[index];
    }

    void displayAll() const {
        for (const auto& item : items) {
            // assume T supports ->display() if T is shared_ptr<Product>
            // or supports display() if T is object with display().
            if constexpr (is_pointer<T>::value) {
                // pointer case (raw pointer) - not recommended but supported
                if (item) item->display();
            } else {
                // attempt to handle smart pointers and objects:
                // if T is shared_ptr<U>, use item->display(); else item.display()
                using ElemType = typename std::decay<decltype(item)>::type;
                // detect shared_ptr by simple approach:
                // Attempt to call arrow operator; if fails at compile-time, fallback to dot.
                // For simplicity, try both forms via overload resolution using lambdas is complex;
                // Since typical usage below is InventoryList<shared_ptr<Product>>, assume -> works.
                item->display();
            }
        }
    }
};

// ======================== CLASS: ShoppingCart ==========================
// Stores product pointers + quantity
struct CartItem {
    shared_ptr<Product> product;
    int quantity;
};

class ShoppingCart : public Discountable {
private:
    vector<CartItem> cartItems;
    double total = 0.0;

public:
    ShoppingCart() = default;

    // Overload += to add a product (shared_ptr<Product>)
    ShoppingCart& operator+=(shared_ptr<Product> p) {
        if (!p) {
            cout << "Cannot add null product pointer to cart.\n";
            return *this;
        }

        if (p->getStock() <= 0) {
            cout << "Cannot add " << p->getName() << " (out of stock)\n";
            return *this;
        }

        // If product exists in cart, increase quantity
        bool found = false;
        for (auto& item : cartItems) {
            if (*item.product == *p) {
                item.quantity++;
                found = true;
                break;
            }
        }
        if (!found) {
            CartItem ci{ p, 1 };
            cartItems.push_back(ci);
        }

        total += p->getPrice();
        p->updateStock(-1); // decrement inventory
        return *this;
    }

    // Remove one unit of product by id (returns true if removed)
    bool removeOneById(const string& id) {
        for (size_t i = 0; i < cartItems.size(); ++i) {
            if (cartItems[i].product->getId() == id) {
                total -= cartItems[i].product->getPrice();
                cartItems[i].quantity--;
                cartItems[i].product->updateStock(1); // return one to stock
                if (cartItems[i].quantity <= 0) {
                    cartItems.erase(cartItems.begin() + i);
                }
                return true;
            }
        }
        return false;
    }

    void display() const {
        cout << "=== Cart Contents ===\n";
        if (cartItems.empty()) {
            cout << "(empty)\n";
        } else {
            for (const auto& item : cartItems) {
                cout << item.quantity << "x ";
                item.product->display();
            }
        }
        cout << "Total: $" << fixed << setprecision(2) << total << "\n";
    }

    // Apply discount to total (mutates total)
    double applyDiscount(double rate) override {
        if (rate < 0.0 || rate > 1.0) {
            cout << "Invalid discount rate. No change.\n";
            return total;
        }
        total = total * (1.0 - rate);
        return total;
    }

    double getTotal() const { return total; }
};

// ======================== CLASS: Order ==========================
class Order {
private:
    string orderId;
    ShoppingCart cart;

public:
    Order(const string& id, const ShoppingCart& c)
        : orderId(id), cart(c) {}

    void display() const {
        cout << "\n=== Order " << orderId << " ===\n";
        cart.display();
    }
};

// ======================== TESTING MAIN ==========================
int main() {
    cout << "=== E-COMMERCE PRODUCT MANAGEMENT DEMO ===\n\n";

    // Create some products
    auto p1 = make_shared<Product>("P01", "Book: C++ Basics", 15.00, 5);
    auto p2 = make_shared<Electronics>("E01", "Laptop Pro", 1200.00, 2, 24);
    auto p3 = make_shared<Clothing>("C01", "T-Shirt", 20.00, 3, "L");
    auto p4 = make_shared<Product>("P02", "Notebook", 3.50, 0); // out of stock example

    // Inventory using template
    InventoryList<shared_ptr<Product>> inventory;
    inventory.add(p1);
    inventory.add(p2);
    inventory.add(p3);
    inventory.add(p4);

    cout << "--- INVENTORY ---\n";
    inventory.displayAll();

    // Shopping cart demo
    ShoppingCart cart;
    cart += p1; // add book
    cart += p2; // add laptop
    cart += p3; // add t-shirt
    cart += p2; // add laptop again -> quantity 2
    cart += p2; // attempt third laptop -> should fail due to stock
    cart += p4; // attempt to add out-of-stock

    cout << "\n--- CART BEFORE DISCOUNT ---\n";
    cart.display();

    // Remove one T-Shirt
    cout << "\nRemoving one T-Shirt (if exists)...\n";
    bool removed = cart.removeOneById("C01");
    cout << (removed ? "Removed one unit.\n" : "No such item in cart.\n");

    cout << "\n--- CART AFTER REMOVAL ---\n";
    cart.display();

    // Apply discount polymorphically
    cout << "\nApplying 10% discount to cart...\n";
    cart.applyDiscount(0.10);
    cart.display();

    // Compare products
    cout << "\nCompare p1 and p2: " << ((*p1 == *p2) ? "same" : "different") << "\n";
    cout << "Compare p1 and p1: " << ((*p1 == *p1) ? "same" : "different") << "\n";

    // Create an order from cart
    Order order1("O001", cart);
    order1.display();

    cout << "\nDemo finished.\n";
    return 0;
}
