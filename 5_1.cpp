#include <algorithm>
#include <any>
#include <cctype>
#include <cstddef>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <map>
#include <regex>
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

bool seriesIsCorrect(std::vector<int> &numbers,
                     std::map<int, std::vector<int>> &rules) {
  for (int i = 1; i < numbers.size(); i++) {
    for (int j = 0; j < i; j++) {
      if (std::ranges::find(rules[numbers[i]], numbers[j]) !=
          rules[numbers[i]].end()) {
        return false;
      }
    }
  }
  return true;
}

int main() {
  std::ifstream in("5_rules.txt");
  std::string line;
  std::vector<std::string> lines;
  unsigned long long count = 0;
  std::map<int, std::vector<int>> rules;
  while (std::getline(in, line)) {
    lines.push_back(line);
    auto numbers = split(line, "|");
    rules[std::stoi(numbers[0])].push_back(std::stoi(numbers[1]));
  }

  lines.clear();
  in.close();

  std::ifstream ser("5_series.txt");
  while (std::getline(ser, line)) {
    lines.push_back(line);
    auto numbers = splitAsInt(line, ",");
    if (seriesIsCorrect(numbers, rules)) {
      count += numbers[numbers.size() / 2];
    }
  }

  std::cout << count << std::endl;
  return 0;
}
