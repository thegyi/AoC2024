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

void createOperators(std::vector<std::vector<char>> &signs, unsigned int n) {
  std::vector<std::vector<char>> ret;
  if (signs.empty()) {
    signs.emplace_back();
  }
  if (n > 0) {
    size_t originalSize = signs.size();
    signs.reserve(signs.size() * 3);

    for (size_t i = 0; i < originalSize; ++i) {
      std::vector<char> current = std::move(signs[i]);

      // Generate new combinations
      signs[i] = current; // Reuse the current slot
      signs[i].push_back('+');

      auto starVariant = current;
      starVariant.push_back('*');
      signs.push_back(std::move(starVariant));

      auto pipeVariant = current;
      pipeVariant.push_back('|');
      signs.push_back(std::move(pipeVariant));
    }

    createOperators(signs, n - 1); // Recursive call
  }
}

struct position {
  int x;
  int y;

  position(int x, int y) : x(x), y(y) {}

  position operator+(const position &other) const {
    return position(x + other.x, y + other.y);
  }

  position operator-(const position &other) const {
    return position(x - other.x, y - other.y);
  }

  bool isValid(int rowMax, int colMax) {
    return x >= 0 && x < rowMax && y >= 0 && y < colMax;
  }

  bool operator==(const position &other) const {
    return x == other.x && y == other.y;
  }

  bool operator!=(const position &other) const { return !(*this == other); }

  bool operator<(const position &other) const {
    return x < other.x || (x == other.x && y < other.y);
  }
};

int main() {
  std::ifstream in("8.txt");
  std::string line;
  std::vector<std::string> lines;
  unsigned long long sum = 0;
  while (std::getline(in, line)) {
    lines.push_back(line);
  }
  std::map<char, std::vector<position>> antennas;

  for (int i = 0; i < lines.size(); i++) {
    for (int j = 0; j < lines[i].size(); j++) {
      if (std::isdigit(lines[i][j]) || std::isalpha(lines[i][j])) {
        antennas[lines[i][j]].push_back(position(i, j));
      }
    }
  }
  std::set<position> uniquePositions;
  for (const auto &[antennaCode, antennaPositions] : antennas) {
    for (int i = 0; i < antennaPositions.size(); i++) {
      for (int j = i + 1; j < antennaPositions.size(); j++) {
        auto p1 = antennaPositions[j] - antennaPositions[i];
        position antinode1 = antennaPositions[i] - p1;
        position antinode2 = antennaPositions[j] + p1;
        if (antinode1.isValid(lines.size(), lines[0].size())) {
          uniquePositions.emplace(antinode1);
        }
        if (antinode2.isValid(lines.size(), lines[0].size())) {
          uniquePositions.emplace(antinode2);
        }
      }
    }
  }
  std::cout << uniquePositions.size() << std::endl;
  return 0;
}
