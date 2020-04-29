#ifndef UTILS_H
#define UTILS_H

#include <string>
#include <vector>
#include <regex>
#include <sstream>
#include <fstream>
#include <algorithm>
using namespace std;

vector<string> split(string stringToSplit, string delimeter);
string filterNumbers(string input);
bool checkFileExists(string filename);
int toInt(const string&, const char*);

#endif // UTILS_H
