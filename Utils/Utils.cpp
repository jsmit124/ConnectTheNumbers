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

/// Returns true if the file [filename] exists
// @param filename: the name of the file to check
// @return true if file exists; otherwise false
bool checkFileExists(const string& filename)
{
    ifstream inFile(filename);
    bool good = inFile.good();
    inFile.close();

    return good;
}

/// Returns input filtered to only numbers
// @param input: the input strign to strip
// @return string formatted to only #'s
string filterNumbers(string input)
{
    return regex_replace(input, regex(R"([\D])"), "");
}

/// Converst the text to int
// @param text: to convert
// @param errorMessage: the message to throw
// @return int from conversion
int toInt(const string& text, const char* errorMessage)
{
    istringstream streamConversion(text);
    int value = 0;
    if (!(streamConversion >> value))
    {
        throw errorMessage;
    }

    return value;
}

/// Formats the seconds to a specfied string
// @param totalSeconds: the seconds to format
// @return string formatted to time format
string formatDurationHoursSeconds(int totalSeconds)
{
    int minutes = totalSeconds / SECONDS_IN_A_MINUTE;
    int seconds = totalSeconds % SECONDS_IN_A_MINUTE;

    ostringstream durationOutput;
    durationOutput << setw(2) << setfill('0') << minutes;
    durationOutput << ":";
    durationOutput << setw(2) << setfill('0') << seconds;
    return durationOutput.str();
}
