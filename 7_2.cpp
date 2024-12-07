#include <algorithm>
#include <any>
#include <cctype>
#include <cstddef>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <map>
#include <regex>
#include <set>
#include <stdexcept>
#include <string>
#include <utility>
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

std::vector<int> splitAsInt(std::string str, const std::string delimiter) {
  size_t pos = 0;
  std::string token;
  std::vector<int> result;
  while ((pos = str.find(delimiter)) != std::string::npos) {
    token = str.substr(0, pos);
    result.push_back(std::stoi(token));
    str.erase(0, pos + delimiter.length());
  }
  result.push_back(std::stoi(str));
  return result;
};

void createSigns(std::vector<std::vector<char>> &signs, int n) {
  std::vector<std::vector<char>> ret;
  if (signs.empty()) {
    signs.push_back(std::vector<char>());
  }
  if (n > 0) {
    std::vector<std::vector<char>> res;
    for (auto s : signs) {
      s.push_back('+');
      res.push_back(s);
      s.back() = '*';
      res.push_back(s);
      s.back() = '|';
      res.push_back(s);
    }
    signs = std::vector<std::vector<char>>(res.begin(), res.end());
    createSigns(signs, n - 1);
  }
}

int main() {
  std::ifstream in("7.txt");
  std::string line;
  std::vector<std::string> lines;
  unsigned long long sum = 0;
  while (std::getline(in, line)) {
    lines.push_back(line);
    auto numbers = split(line, ":");
    unsigned long long int result = stoll(numbers[0]);
    auto operands = split(numbers[1], " ");
    operands.erase(operands.begin());
    std::vector<std::vector<char>> signs;
    signs.emplace_back(std::vector<char>());
    createSigns(signs, operands.size() - 1);
    for (auto s : signs) {
      unsigned long long int res = std::stoi(operands[0]);
      for (int i = 0; i < s.size(); i++) {
        if (s[i] == '*') {
          res *= std::stoll(operands[i + 1]);
        }
        if (s[i] == '+') {
          res += std::stoll(operands[i + 1]);
        }
        if (s[i] == '|') {
          res = std::stoll(std::to_string(res) + operands[i + 1]);
        }
      }
      if (result == res) {
        sum += res;
        break;
      }
    }
  }

  std::cout << sum << std::endl;
  return 0;
}
