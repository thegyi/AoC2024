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

bool isIncreasing(std::vector<std::string> v) {
  for (unsigned int i = 1; i < v.size(); i++) {
    if (std::stoi(v[i]) <= std::stoi(v[i - 1])) {
      return false;
    }
  }
  return true;
}

bool isDecreasing(std::vector<std::string> v) {
  for (unsigned int i = 1; i < v.size(); i++) {
    if (std::stoi(v[i]) >= std::stoi(v[i - 1])) {
      return false;
    }
  }
  return true;
}

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
  std::ifstream in("input.txt");
  std::string line;
  int countOfSafeReports = 0;
  while (std::getline(in, line)) {
    auto numbers = split(line, " ");
    for (std::size_t i = 0; i < numbers.size(); i++) {
      std::vector<std::string> numbers2 = numbers;
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