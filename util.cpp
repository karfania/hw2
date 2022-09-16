#include <iostream>
#include <sstream>
#include <cctype>
#include <algorithm>
#include "util.h"

using namespace std;
std::string convToLower(std::string src)
{
    std::transform(src.begin(), src.end(), src.begin(), ::tolower);
    return src;
}

/** Complete the code to convert a string containing a rawWord
    to a set of words based on the criteria given in the assignment **/
std::set<std::string> parseStringToWords(string rawWords)
{

    std::set<std::string> keyWords;
    rawWords = convToLower(rawWords); // making common case
    size_t count = 0; // tracks length of (possible) keyword
    size_t tempStart = 0; // tracks new beginning after split
    for (size_t i = 0; i < rawWords.size() ; i++)
    {
        // if current character is a letter
        if (isalpha(rawWords[i]))
        {
            // add 1 to count
            count++;
            // edge case where we are at the last element but count is 2+
            if (i == rawWords.size() - 1 && count >= 2)
            {
                // add substring from tempStart of length count to the set
                keyWords.insert(rawWords.substr(tempStart, count));
            }

        // if the current character is not a letter
        } else
        {
            // if the string before punctuation is long enough, add to set
            if (count >= 2)
            {
                // add substring from tempStart of length count to the set
                keyWords.insert(rawWords.substr(tempStart, count));
            }

            // update new start to be after punctuation, reset count
            tempStart = i + 1;
            count = 0;
        }
    }

    return keyWords;


}

/**************************************************
 * COMPLETED - You may use the following functions
 **************************************************/

// Used from http://stackoverflow.com/questions/216823/whats-the-best-way-to-trim-stdstring
// trim from start
std::string &ltrim(std::string &s) {
    s.erase(s.begin(), 
	    std::find_if(s.begin(), 
			 s.end(), 
			 std::not1(std::ptr_fun<int, int>(std::isspace))));
    return s;
}

// trim from end
std::string &rtrim(std::string &s) {
    s.erase(
	    std::find_if(s.rbegin(), 
			 s.rend(), 
			 std::not1(std::ptr_fun<int, int>(std::isspace))).base(), 
	    s.end());
    return s;
}

// trim from both ends
std::string &trim(std::string &s) {
    return ltrim(rtrim(s));
}

// int main(int argc, char* argv[])
// {
//     std::set<std::string> test1 = parseStringToWords("Men's");
//     for (std::set<string>::iterator it = test1.begin();
//          it != test1.end(); ++it)
//         {
//             cout << *it << endl;
//         }
//         cout << endl;

//     std::set<std::string> test2 = parseStringToWords("Amazon's new device");
//     for (std::set<string>::iterator it = test2.begin();
//          it != test2.end(); ++it)
//         {
//             cout << *it << endl;
//         }
//         cout << endl;

//     std::set<std::string> unionized = setUnion(test1, test2);
//     for (std::set<string>::iterator it = unionized.begin();
//          it != unionized.end(); ++it)
//         {
//             cout << *it << endl;
//         }
//         cout << endl;

//     std::set<std::string> intersected1 = setIntersection(test1, test2);
//     for (std::set<string>::iterator it = intersected1.begin();
//          it != intersected1.end(); ++it)
//         {
//             cout << *it << endl;
//         }
//         cout << endl;
    

//     std::set<std::string> test3 = parseStringToWords("Apples's new device");
//     std::set<std::string> intersected2 = setIntersection(test2, test3);
//     for (std::set<string>::iterator it = intersected2.begin();
//          it != intersected2.end(); ++it)
//         {
//             cout << *it << endl;
//         }
//         cout << endl;
// }

