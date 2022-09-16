#include "product.h"

class Book : public Product {
public:
    Book(const std::string category, const std::string name, double price, int qty, const std::string isbn, const std::string author); // constructor
    virtual ~Book(); // destructor

    // Overwritten functions, polymorphically
    // inherited from the Product class
    std::set<std::string> keywords() const; 
    std::string displayString() const;
    void dump(std::ostream& os) const;

// Data Members:
private:
    std::string isbn_;
    std::string author_;
};