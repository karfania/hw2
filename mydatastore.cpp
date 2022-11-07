#include "mydatastore.h"
#include "util.h"
#include <iostream>


// Empty Constructor
MyDataStore::MyDataStore()
{

}

// Deconstructor
MyDataStore::~MyDataStore()
{
    // Deleting products from ProductStore --> all products deleted
    std::vector<Product*>::iterator prodIt;
    for (prodIt = productStore.begin(); prodIt != productStore.end(); ++prodIt)
    {
        delete *prodIt;
    }

    // Deleting users from UserStore --> all users (and keys) deleted
    std::map<std::string, User*>::iterator userIt;
    for (userIt = userStore.begin(); userIt != userStore.end(); ++userIt)
    {
        delete userIt -> second;
    }
}

// Adding product to set that stores all products for an instance of the program
// Products stored in a set
// Mapping bewteen product object and a set of its keywords made
void MyDataStore::addProduct(Product* p)
{
    // Add product to Product Set/Store
    productStore.push_back(p);

    // Grab keywords from product (already lower case) and add to 
    // data member mapping a product to its keywords
    std::set<std::string> productKeywords = p -> keywords();
    std::set<std::string>::iterator keywordIt;
    
    for (keywordIt = productKeywords.begin(); keywordIt != productKeywords.end(); ++keywordIt)
    {
        // Iterator to check the map containing keywords and a vector of Product*'s
        std::map<std::string, std::vector<Product*>>::iterator keywordMapIt = keywordStore.find(*keywordIt);

        // If the keyword has already been added to map, just push product to the existing vector
        if (keywordMapIt != keywordStore.end())
        {
            (keywordMapIt -> second).push_back(p);
        } 
        
        // If the keyword does not yet exist, then insert a new key with the appropriate value
        else
        {
            std::vector<Product*> prodVector;
            prodVector.push_back(p);
            keywordStore.insert(std::make_pair(*keywordIt, prodVector));
        }
        
    }

}

// Adding users to a map that stores all products for an instance of the program
// Mapping bewteen user's name and a user object
void MyDataStore::addUser(User* u)
{
    // Add user to User Set/Store
    // Mapping user's name to user object
    std::string userName = u -> getName();
    userName = convToLower(userName);
    userStore.insert(std::make_pair(userName, u));

    // Create an empty cart for the User
    std::deque<Product*> products;
    userCart.insert(std::make_pair(userName, products));

}

std::vector<Product*> MyDataStore::search(std::vector<std::string>& terms, int type)
{
    // Type 0 -> AND search -> intersection
    // Type 1 -> OR search -> union
    std::vector<Product*> matchingProducts;

    // Iterate through each term, store keywords in new set
    std::vector<std::string>::iterator termsIt;
    std::set<Product*> set1;
    std::set<Product*> set2;
    int instance = 1;
    for (termsIt = terms.begin(); termsIt != terms.end(); ++termsIt)
    {
        // find key, add all products in vector to set1
        std::map<std::string, std::vector<Product*>>::iterator keyIt = keywordStore.find(*termsIt);
        if (keyIt != keywordStore.end())
            {
                std::vector<Product*>::iterator prodIt;
                for (prodIt = (keyIt -> second).begin(); prodIt != (keyIt -> second).end(); ++prodIt)
                {
                    //std::cout << (*prodIt) -> displayString() << std::endl;
                    // if it's the first time running, also add it to set2!
                    if (instance == 1)
                    {
                        set2.insert(*prodIt);
                    }
                    set1.insert(*prodIt);
                }
                instance++;
            

            // Call setUnion or setIntersection and update set2 accordingly
            // continue to call on all terms until complete: 

            // Intersection
            if (type == 0)
            {
                set2 = setIntersection(set1, set2);
            }

            // Union
            else
            {
                set2 = setUnion(set1, set2);
            }

            // Clear set1 so products matching the next term are added to clean set
            set1.clear();
        }
    }

    // Push all elements in set2 (which stored the cumulative intersections/unions) 
    // to matchingProducts, which will be returned
    std::set<Product*>::iterator prodIt2;
    for (prodIt2 = set2.begin(); prodIt2 != set2.end(); ++prodIt2)
    {
        matchingProducts.push_back(*prodIt2);
    }

    return matchingProducts;
    
}

// Writing updates/additions to output file
// Following formatting given in instructions
void MyDataStore::dump(std::ostream& ofile)
{
    // Writing product "header" to the output file
    ofile << "<products>" << std::endl;

    // Writing product information, iterating through stored
    // products and leveraging the dump method
    std::vector<Product*>::iterator prodIt;
    for (prodIt = productStore.begin(); prodIt != productStore.end(); ++prodIt)
    {
        (*prodIt) -> dump(ofile);
    }

    // Writing the product section "break" to output file
    ofile << "</products>" << std::endl;

    // Writing user "header" to the output file
    ofile << "<users>" << std::endl;

    // Writing user information, iterating through stored
    // users and leveraging the dump method
    std::map<std::string, User*>::iterator userIt;
    for (userIt = userStore.begin(); userIt != userStore.end(); ++userIt)
    {
        userIt -> second -> dump(ofile);
    }

    // Writing the user section "break" to output file
    ofile << "</users>" << std::endl;
}

// Adding to a cart, which is the data member userCart
void MyDataStore::addCart(std::string userName, Product* p)
{
    // Ensuring user and product exists
    std::map<std::string, User*>::iterator userIt = userStore.find(convToLower(userName));
    std::vector<Product*>::iterator productIt = find(productStore.begin(), productStore.end(), p);

    // If both exist, process the request by adding user and product to the end of the map
    if (userIt != userStore.end() && productIt != productStore.end())
    {
        // Find the user's specific cart  
        std::map<std::string, std::deque<Product*>>::iterator userCartIt = userCart.find(userName);
        if (userCartIt != userCart.end())
        {
            // Add the product to the user's cart maintaning FIFO order
            (userCartIt -> second).push_back(p);
        }
    }

    // If either don't exist, print error to screen and don't process command
    else
    {
        std::cout << "Invalid request" << std::endl;
        return;
    }
}

void MyDataStore::viewCart(std::string userName)
{
    int count = 1; // to provide indexing/sizing
    // Ensuring user and their cart exists
    //userName = convToLower(userName);
    std::map<std::string, User*>::iterator userIt = userStore.find(convToLower(userName));
    if (userIt != userStore.end())
    {
        // Find the specific cart and, if it exists, iterate through the deque of Product*'s
        std::map<std::string, std::deque<Product*>>::iterator userCartIt = userCart.find(convToLower(userName));
        if (userCartIt != userCart.end())
        {
            std::deque<Product*>::iterator prodIt;

            // If cart for user is empty, notify them
            if ((userCartIt -> second).begin() == (userCartIt -> second).end())
            {
                std::cout << "Cart is empty!" << std::endl;
            } 

            // If it's not empty, then iterate through the cart and print each object
            else
            {
                for (prodIt = (userCartIt -> second).begin(); prodIt != (userCartIt -> second).end(); ++prodIt)
                {
                    std::cout << "Item " << count << std::endl;
                    std::string prodOut = (*prodIt) -> displayString(); //or just product name ?
                    std::cout << prodOut << "\n" << std::endl;
                    count++;
                }
            }
            
        }
    }

    // If the user does not exist, print error to screen and don't process command
    else
    {
        std::cout << "Invalid username" << std::endl;
        return;
    }
}

// Buying a user's cart
void MyDataStore::buyCart(std::string userName)
{
    // Ensuring the user exists
    std::map<std::string, User*>::iterator userIt = userStore.find(userName);
     if (userIt != userStore.end())
    {

        // Access the user's cart to iterate through products
        std::map<std::string, std::deque<Product*>>::iterator userCartIt = userCart.find(userName);
        if (userCartIt != userCart.end())
        {
            // If the user's cart is empty, notify them
            if ((userCartIt -> second).begin() == (userCartIt -> second).end())
            {
                std::cout << "Cart is empty!" << std::endl;
            }
            else
            {
                //std::deque<Product*>::iterator prodIt;
                //for (prodIt = (userCartIt -> second).begin(); prodIt != (userCartIt -> second).end(); ++prodIt)
                int countIterationsBound = (userCartIt -> second).size();
                //int index = 0;
                while (countIterationsBound > 0)
                {
                    double prodPrice = (userCartIt -> second)[0] -> getPrice();
                    int prodQty = (userCartIt -> second)[0] -> getQty();

                    // If the product is in stock AND the user can afford it,
                    // remove from cart, reduce quantity, and debit user
                    if (prodQty > 0 && ((userIt -> second -> getBalance()) - prodPrice >= 0))
                    {
                        std::cout << "Purchased " << userCartIt -> second[0] -> getName() << std::endl;
                        (userCartIt -> second)[0] -> subtractQty(1);
                        userIt -> second -> deductAmount(prodPrice);

                        // Purchased so pop it, therefore new front is what we are checking
                        (userCartIt -> second).pop_front();
                    }

                    // If either condition isn't met, push_back item so it remains in cart, then pop to check new item
                    else
                    {
                        std::cout << "Couldn't purchase " << userCartIt -> second[0] -> getName() << std::endl;
                        (userCartIt -> second).push_back(userCartIt ->second[0]);
                        (userCartIt -> second).pop_front();
                        
                    }

                    countIterationsBound--;
                }
            }
        }
    }

    // If the user does not exist, print error to the screen and don't process command
    else
    {
        std::cout << "Invalid username" << std::endl;
        return;
    }

}




