#include <algorithm>
#include <cctype>
#include <cstddef>
#include <cstdlib>
#include <fstream>
#include <functional>
#include <iostream>
#include <iterator>
#include <map>
#include <string>
#include <vector>
  
/**
 * @brief Splits a string into a vector of strings using a delimiter.
 *
 * @param str The string to split.
 * @param delimiter The delimiter to split by.
 *
 * @return A vector of strings, each representing a substring of @p str
 *         separated by @p delimiter.
 */
std::vector<std::string> split(std::string str, const std::string delimiter) {
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
 * @brief Checks if a sequence of numbers is strictly increasing.
 *
 * Iterates through a vector of strings representing numbers and
 * verifies that each number is greater than the preceding number.
 *
 * @param v A vector of strings representing a sequence of numbers.
 *
 * @return @c true if each number is greater than the preceding number,
 *         @c false otherwise.
 */
bool isIncreasing(std::vector<std::string> &v) {
  for (unsigned int i = 1; i < v.size(); i++) {
    if (std::stoi(v[i]) <= std::stoi(v[i - 1])) {
      return false;
    }
  }
  return true;
}

/**
 * @brief Checks if a sequence of numbers is strictly decreasing.
 *
 * Iterates through a vector of strings representing numbers and
 * verifies that each number is less than the preceding number.
 *
 * @param v A vector of strings representing a sequence of numbers.
 * @return true if the sequence is strictly decreasing, false otherwise.
 */
bool isDecreasing(std::vector<std::string> &v) {
  for (unsigned int i = 1; i < v.size(); i++) {
    if (std::stoi(v[i]) >= std::stoi(v[i - 1])) {
      return false;
    }
  }
  return true;
}

/**
 * @brief Checks if a sequence of numbers is "safe" according to the following
 * rules.
 *
 * A sequence is "safe" if it is either increasing or decreasing and the
 * absolute difference between any two consecutive numbers is never greater than
 * 3 and never less than 1.
 */
bool isSafe(std::vector<std::string> &s) {
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
    for (std::size_t i = 0; i < numbers.size(); i++) {
      std::vector<std::string> numbers2(numbers);
      numbers2.erase(numbers2.begin() + i);
      if (isSafe(numbers2)) {
        countOfSafeReports++;
        break;
      }
    }
  }
  std::cout << countOfSafeReports << std::endl;
  return 0;
}
