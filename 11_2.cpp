#include <cctype>
#include <cstddef>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <map>
#include <memory>
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

unsigned long long
countOfNumbers(std::map<std::pair<unsigned long long, unsigned long long>,
                        unsigned long long> &solutions,
               unsigned long long n, int iteration) {
  if (iteration == 0) {
    return 1;
  }
  if (solutions.find(std::make_pair(iteration, n)) != solutions.end()) {
    return solutions.find(std::make_pair(iteration, n))->second;
  }
  if (n == 0) {
    return countOfNumbers(solutions, 1, iteration - 1);
  } else {
    std::string sn = std::to_string(n);
    if (sn.size() % 2 == 0) {
      std::string left = sn.substr(0, sn.size() / 2);
      std::string right = sn.substr(sn.size() / 2);
      solutions[std::make_pair(iteration - 1, std::stoll(left))] =
          countOfNumbers(solutions, std::stoll(left), iteration - 1);
      solutions[std::make_pair(iteration - 1, std::stoll(right))] =
          countOfNumbers(solutions, std::stoll(right), iteration - 1);

      return solutions[std::make_pair(iteration - 1, std::stoll(left))] +
             solutions[std::make_pair(iteration - 1, std::stoll(right))];
    } else {
      solutions[std::make_pair(iteration - 1, n * 2024)] =
          countOfNumbers(solutions, n * 2024, iteration - 1);
      return solutions[std::make_pair(iteration - 1, n * 2024)];
    }
  }
}

int main() {
  // std::ifstream in("input.txt");
  // std::string line;
  std::vector<unsigned long long int> lines{28, 4,       3179, 96938,
                                            0,  6617406, 490,  816207};

  std::map<std::pair<unsigned long long, unsigned long long>,
           unsigned long long>
      solutions;

  unsigned long long sum = 0;
  // for (int i = 1; i <= 75; i++) {
  std::vector<unsigned long long int> tmp;
  for (int j = 0; j < lines.size(); j++) {

    sum += countOfNumbers(solutions, lines[j], 75);
  }
  lines = tmp;
  //}

  std::cout << sum << std::endl;
  return 0;
}