#include "product.h"
#include "movie.h"
#include "util.h"

// Constructor
Movie::Movie(const std::string category, const std::string name, double price, int qty, const std::string genre, const std::string rating):
    Product::Product(category, name, price, qty),
    genre_(genre),
    rating_(rating)
    {

    }

// Destructor
Movie::~Movie()
{

}

// Keywords function
std::set<std::string> Movie::keywords() const
{
    std::set<std::string> keywords;
    std::set<std::string> genre = parseStringToWords(genre_);
    std::set<std::string> name = parseStringToWords(getName());

    // Adding genre information
    for (std::set<std::string>::iterator it = genre.begin();
         it != genre.end(); ++it)
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
std::string Movie::displayString() const
{
    // Initialize string
    std::string display = "";

    // First line
    display.append(Product::getName());
    display.append("\n");

    // Second line
    display.append("Genre: ");
    display.append(genre_);
    display.append(" Rating: ");
    display.append(rating_);
    display.append("\n");

    // Third Line
    display.append(std::to_string(price_));
    display.append(" ");
    display.append(std::to_string(qty_));
    display.append(" left.");

    return display;
}

// Dump Function
void Movie::dump(std::ostream& os) const
{
    os << category_ << "\n" << name_ << "\n" << price_ << "\n" << qty_ << 
    genre_ << rating_ << std::endl;
}
