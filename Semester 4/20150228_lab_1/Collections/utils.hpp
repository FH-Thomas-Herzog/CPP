#ifndef UTILS_HPP_INCLUDED
#define UTILS_HPP_INCLUDED

#include <string>
#include <fstream>

bool isPunct(char ch);
bool isDigit(char ch);
bool isAlpha(char ch);
char toLower(char ch);
std::string normalize(std::string word);
void openStream(int argc, char *argv[], std::ifstream &fin);

#endif // UTILS_HPP_INCLUDED
