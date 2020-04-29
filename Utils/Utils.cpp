#include "Utils.h"

/// Splits [stringToSplit] by the given [delimeter] and returns a vector of all the split strings.
//
// @precondition: none
// @postcondition: none
// @param stringToSplit: the string to split
// @param delimeter: the string to split by
// @return a vector of split strings.
vector<string> split(string stringToSplit, string delimeter)
{
    vector<string> splittedString;
    int startIndex = 0;
    int  endIndex = 0;

    while( (endIndex = stringToSplit.find(delimeter, startIndex)) < stringToSplit.size() )
    {
        string val = stringToSplit.substr(startIndex, endIndex - startIndex);
        splittedString.push_back(val);
        startIndex = endIndex + delimeter.size();
    }

    if(startIndex < stringToSplit.size())
    {
        string val = stringToSplit.substr(startIndex);
        splittedString.push_back(val);
    }

    return splittedString;
}

string filterNumbers(string input)
{
    return regex_replace(input, regex(R"([\D])"), "");
}
