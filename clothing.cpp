#include "product.h"
#include "clothing.h"
#include "util.h"

#include "product.h"
#include "book.h"
#include "util.h"

// Constructor
Clothing::Clothing(const std::string category, const std::string name, double price, int qty, const std::string size, const std::string brand):
    Product::Product(category, name, price, qty),
    size_(size),
    brand_(brand)
    {

    }

// Destructor
Clothing::~Clothing()
{

}

// Keywords function
std::set<std::string> Clothing::keywords() const
{
    std::set<std::string> keywords;
    std::set<std::string> brand = parseStringToWords(brand_);
    std::set<std::string> name = parseStringToWords(getName());

    // Adding brand information
    for (std::set<std::string>::iterator it = brand.begin();
         it != brand.end(); ++it)
        {
            keywords.insert(*it);
        }

    // Adding product name information
    for (std::set<std::string>::iterator it = name.begin();
        it != name.end(); ++it)
        {
            keywords.insert(*it);
        }

    return keywords;
}

// Display String function
std::string Clothing::displayString() const
{
    // Initialize string
    std::string display = "";

    // First line
    display.append(Product::getName());
    display.append("\n");

    // Second line
    display.append("Size: ");
    display.append(size_);
    display.append(" Brand: ");
    display.append(brand_);
    display.append("\n");

    // Third Line
    display.append(std::to_string(price_));
    display.append(" ");
    display.append(std::to_string(qty_));
    display.append(" left.");

    return display;
}

// Dump Function
void Clothing::dump(std::ostream& os) const
{
    os << category_ << "\n" << name_ << "\n" << price_ << "\n" << qty_ << 
    size_ << brand_ << std::endl;
}
