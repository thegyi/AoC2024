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
 * @brief Splits a string by a delimiter and returns a vector of strings.
 *
 * The function takes a string and a delimiter as parameters.
 * It iterates over the string and when it finds the delimiter,
 * it takes the substring from the beginning of the original string
 * to the position of the delimiter and adds it to a vector of strings.
 * Then it removes the taken substring from the original string.
 * The function repeats this process until the delimiter is not found in the
 * string. At the end, the function adds the remaining string to the vector of
 * strings and returns it.
 *
 * @param str The string to be split.
 * @param delimiter The delimiter to split by.
 * @return A vector of strings.
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
  unsigned long long int result = 0;
  while (std::getline(in, line)) {
    std::regex word_regex("mul\\((\\d+),(\\d+)\\)");
    auto words_begin =
        std::sregex_iterator(line.begin(), line.end(), word_regex);
    auto words_end = std::sregex_iterator();
    while (words_begin != words_end) {
      result += mul(words_begin->str());
      words_begin++;
    }
  }
  std::cout << result << std::endl;
  return 0;
}