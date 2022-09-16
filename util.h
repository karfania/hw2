#ifndef UTIL_H
#define UTIL_H

#include <string>
#include <iostream>
#include <set>


/** Complete the setIntersection and setUnion functions below
 *  in this header file (since they are templates).
 *  Both functions should run in time O(n*log(n)) and not O(n^2)
 */
template <typename T>
std::set<T> setIntersection(std::set<T>& s1, std::set<T>& s2)
{
    std::set<T> finalSet;

    // iterate through s1
    for (typename std::set<T>::iterator it = s1.begin(); 
         it != s1.end(); ++it)
        {
            // if you can find current s1 element in s2, add it to 
            // set containing the intersection
            if (s2.find(*it) != s2.end())
            {
                finalSet.insert(*it);
            }
        }

        return finalSet;
}

template <typename T>
std::set<T> setUnion(std::set<T>& s1, std::set<T>& s2)
{
    std::set<T> finalSet;

    // O(n)
    // iterate through s1
    for (typename std::set<T>::iterator it = s1.begin(); 
         it != s1.end(); ++it)
        {
            // immediately add s1 to set containing the union
            finalSet.insert(*it);
        }

    // O(n * log(n))
    // iterate through s2
    for (typename std::set<T>::iterator it = s2.begin(); 
         it != s2.end(); ++it)
        {
            // if you can't find element from s2 in s1, add it to
            // set containing the union
            if (s1.find(*it) == s1.end())
            {
                finalSet.insert(*it);
            }
        }

    // Time Complexity: O(2n * logn) --> O(n * log(n))

    return finalSet;
}

/***********************************************/
/* Prototypes of functions defined in util.cpp */
/***********************************************/

std::string convToLower(std::string src);

std::set<std::string> parseStringToWords(std::string line);

// Used from http://stackoverflow.com/questions/216823/whats-the-best-way-to-trim-stdstring
// Removes any leading whitespace
std::string &ltrim(std::string &s) ;

// Removes any trailing whitespace
std::string &rtrim(std::string &s) ;

// Removes leading and trailing whitespace
std::string &trim(std::string &s) ;
#endif
