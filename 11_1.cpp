#include <cctype>
#include <cstddef>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <memory>
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

int main() {
  // std::ifstream in("input.txt");
  std::string line;
  std::vector<unsigned long long int> lines{28, 4,       3179, 96938,
                                            0,  6617406, 490,  816207};

  for (int i = 1; i <= 25; i++) {
    std::vector<unsigned long long int> tmp;
    for (int j = 0; j < lines.size(); j++) {

      unsigned long long n = lines[j];
      std::string sn = std::to_string(n);
      if (n == 0) {
        tmp.emplace_back(1);
      } else {
        if (sn.size() % 2 == 0) {
          std::string left = sn.substr(0, sn.size() / 2);
          std::string right = sn.substr(sn.size() / 2);

          tmp.emplace_back(std::stoll(left));
          tmp.emplace_back(std::stoll(right));
        } else {
          tmp.emplace_back(n * 2024);
        }
      }
    }
    lines = tmp;
  }

  std::cout << lines.size() << std::endl;
  return 0;
}