#include "datastore.h"
#include "product.h"
#include "user.h"
#include <map>
#include <vector>
#include <string>
#include <set>
#include <deque>

class MyDataStore : public DataStore
{
    public:

        MyDataStore(); // constructor
        virtual ~MyDataStore(); // destructor

        // Overloaded methods from DataStore
        void addProduct(Product* p);
        void addUser(User* u);
        std::vector<Product*> search(std::vector<std::string>& terms, int type);
        void dump(std::ostream& ofile);

        // Additional functionality
        void addCart(std::string userName, Product* p);
        void viewCart(std::string userName);
        void buyCart(std::string userName);
        


    private:
        std::vector<Product*> productStore; // vector storing pointers to Products
        std::map<std::string, std::vector<Product*> > keywordStore; // key = keyword, value = set of products that include this keyword
        std::map<std::string, User*> userStore; // key = user's name
        std::map<std::string, std::deque<Product*> > userCart; // stores a user's collection of product

};