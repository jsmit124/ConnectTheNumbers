#ifndef UTILS_H
#define UTILS_H

#include <string>
#include <vector>
#include <regex>
#include <sstream>
#include <fstream>
#include <algorithm>
#include <iomanip>
using namespace std;

#define SECONDS_IN_A_MINUTE 60

vector<string> split(string stringToSplit, string delimeter);
string filterNumbers(string input);
bool checkFileExists(const string& filename);
int toInt(const string&, const char*);
string formatDurationHoursSeconds(int totalSeconds);

#endif // UTILS_H
