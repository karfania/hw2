#include "product.h"

class Clothing : public Product {
public:
    Clothing(const std::string category, const std::string name, double price, int qty, const std::string size, const std::string brand); // constructor
    virtual ~Clothing(); // destructor

    // Overwritten functions, polymorphically
    // inherited from the Product class
    std::set<std::string> keywords() const; 
    std::string displayString() const;
    void dump(std::ostream& os) const;

// Data Members:
private:
    std::string size_;
    std::string brand_;
};