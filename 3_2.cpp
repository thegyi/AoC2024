#include <algorithm>
#include <any>
#include <cctype>
#include <cstddef>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <regex>
#include <stdexcept>
#include <string>
#include <vector>

/**
 * @brief Splits a given string by a specified delimiter.
 *
 * This function iterates over the input string, identifying each occurrence of
 * the delimiter. It extracts substrings between delimiters and stores them in a
 * vector. The process continues until no more delimiters are found, at which
 * point the remaining part of the string is added to the vector. The function
 * returns this vector containing the split substrings.
 *
 * @param str The string to be split.
 * @param delimiter The delimiter used to split the string.
 * @return A vector of substrings obtained by splitting the input string.
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
 * @brief Multiply two numbers passed as a string.
 *
 * The function takes a string like "mul(1,2)" and returns 2.
 *
 * @param s The string to parse and multiply.
 * @return The product of the two numbers in the string.
 */
unsigned long long int mul(const std::string &s) {
  auto tmp1 = s.substr(4);
  auto tmp2 = tmp1.substr(0, tmp1.size() - 1);
  auto numbers = split(tmp2, ",");
  if (!std::ranges::all_of(numbers[0],
                           [](char c) { return std::isdigit(c); }) ||
      !std::ranges::all_of(numbers[1],
                           [](char c) { return std::isdigit(c); })) {
    return 0;
  }
  return std::stoll(numbers[0]) * std::stoll(numbers[1]);
}

int main() {
  std::ifstream in("3.txt");
  std::string line;
  unsigned long long result = 0;
  while (std::getline(in, line)) {
    std::regex word_regex("mul\\((\\d+),(\\d+)\\)");
    auto words_begin =
        std::sregex_iterator(line.begin(), line.end(), word_regex);
    auto words_end = std::sregex_iterator();
    while (words_begin != words_end) {
      std::string left(line.begin(), line.begin() + words_begin->position());

      size_t dontPosition = left.rfind("don't()");
      if (dontPosition == std::string::npos) {
        dontPosition = 0;
      }

      size_t doPosition = left.rfind("do()");
      if (doPosition == std::string::npos) {
        doPosition = 0;
      }

      if (dontPosition <= doPosition) {
        result += mul(words_begin->str());
      }

      words_begin++;
    }
  }
  std::cout << result << std::endl;
  return 0;
}