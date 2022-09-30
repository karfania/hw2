#include "product.h"
#include "book.h"
#include "util.h"

// Constructor
Book::Book(const std::string category, const std::string name, double price, int qty, const std::string isbn, const std::string author):
    Product::Product(category, name, price, qty),
    isbn_(isbn),
    author_(author)
    {

    }

// Destructor
Book::~Book()
{

}

// Keywords function
std::set<std::string> Book::keywords() const
{
    std::set<std::string> keywords;
    std::set<std::string> author = parseStringToWords(author_);
    std::set<std::string> name = parseStringToWords(Product::getName());

    // Adding ISBN numbers as-is
    keywords.insert(isbn_);

    // Adding author information
    for (std::set<std::string>::iterator it = author.begin();
         it != author.end(); ++it)
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
std::string Book::displayString() const
{
    // Initialize string
    std::string display = "";

    // First line
    display.append(Product::getName());
    display.append("\n");

    // Second line
    display.append("Author: ");
    display.append(author_);
    display.append(" ISBN: ");
    display.append(isbn_);
    display.append("\n");

    // Third Line
    std::string price = std::to_string(price_);
    std::string priceFormatted = price.substr(0, price.size()-4);
    display.append(priceFormatted + " ");
    display.append(std::to_string(qty_));
    display.append(" left.");

    return display;
}

// Dump Function
void Book::dump(std::ostream& os) const
{
    os << category_ << "\n" << name_ << "\n" << std::fixed << std::showpoint 
    << std::setprecision(2) << price_ << "\n" << qty_ << 
    "\n" << isbn_ << "\n" << author_ << std::endl;
}
