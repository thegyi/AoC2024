#include <algorithm>
#include <cctype>
#include <cstddef>
#include <cstdlib>
#include <fstream>
#include <functional>
#include <iostream>
#include <map>
#include <string>
#include <vector>

/**
 * Splits a given string into a vector of substrings based on the specified
 * delimiter.
 *
 * @param str The input string to be split.
 * @param delimiter The delimiter string used to divide the input string.
 * @return A vector containing the substrings obtained by splitting the input
 * string.
 */
std::vector<std::string> split(std::string str, std::string delimiter) {
  size_t pos = 0;
  std::string token;
  std::vector<std::string> result;
  while ((pos = str.find(delimiter)) != std::string::npos) {
    token = str.substr(0, pos);
    result.push_back(token);
    str.erase(0, pos + delimiter.length());
  }
  result.push_back(str);
  return result;
};

/**
 * Checks whether a given vector of strings is sorted in increasing order.
 *
 * @param v A vector of strings representing the sequence to be checked.
 * @return True if the sequence is in increasing order, false otherwise.
 */
bool isIncreasing(std::vector<std::string> v) {
  for (unsigned int i = 1; i < v.size(); i++) {
    if (std::stoi(v[i]) <= std::stoi(v[i - 1])) {
      return false;
    }
  }
  return true;
}

/**
 * Checks whether a given vector of strings is sorted in decreasing order.
 *
 * @param v A vector of strings representing the sequence to be checked.
 * @return True if the sequence is in decreasing order, false otherwise.
 */
bool isDecreasing(std::vector<std::string> v) {
  for (unsigned int i = 1; i < v.size(); i++) {
    if (std::stoi(v[i]) >= std::stoi(v[i - 1])) {
      return false;
    }
  }
  return true;
}

/**
 * Checks whether a given sequence of strings is safe, meaning that it is either
 * in strictly increasing or strictly decreasing order, and that the absolute
 * difference between consecutive elements is between 1 and 3, inclusive.
 *
 * @param s A vector of strings representing the sequence to be checked.
 * @return True if the sequence is safe, false otherwise.
 */
bool isSafe(std::vector<std::string> s) {
  for (unsigned int i = 1; i < s.size(); i++) {
    int tmp = std::stoi(s[i]);
    int tmp2 = std::stoi(s[i - 1]);
    if (std::abs(tmp - tmp2) > 3 || std::abs(tmp - tmp2) < 1) {
      return false;
    }
  }
  if (!isIncreasing(s) && !isDecreasing(s)) {
    return false;
  }
  return true;
}
int main() {
  std::ifstream in("2.txt");
  std::string line;
  int countOfSafeReports = 0;
  while (std::getline(in, line)) {
    auto numbers = split(line, " ");
    if (isSafe(numbers)) {
      countOfSafeReports++;
    }
  }

  std::cout << countOfSafeReports << std::endl;
  return 0;
}
