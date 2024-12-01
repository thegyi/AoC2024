#include <algorithm>
#include <cctype>
#include <cstdlib>
#include <fstream>
#include <functional>
#include <iostream>
#include <map>
#include <string>
#include <vector>

class Interval {
public:
  int start;
  int end;
  Interval(int start, int end) : start(start), end(end) {}
  bool contains(Interval other) const {
    return contains(other.start) && contains(other.end);
  };
  bool contains(int x) const { return x >= start && x <= end; }

  bool overlaps(Interval other) const {
    return contains(other.start) || contains(other.end) ||
           other.contains(start) || other.contains(end);
  }
};

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

bool unique_string(std::string s) {
  std::map<char, int> freq;
  for (unsigned int i = 0; i < s.size(); i++) {
    if (freq.contains(s[i])) {
      freq[s[i]] = 1;
    } else {
      return false;
    }
  }
  return true;
}

int main() {
  std::ifstream in("1.txt");
  std::string line;
  std::vector<int> left;
  std::vector<int> right;
  while (std::getline(in, line)) {
    auto numbers = split(line, "  ");
    left.push_back(std::stoi(numbers[0]));
    right.push_back(std::stoi(numbers[1]));
  }
  std::ranges::sort(left);
  std::ranges::sort(right);
  unsigned long long int sum = 0;
  for (unsigned int i = 0; i < left.size(); i++) {
    sum += std::abs(left[i] - right[i]);
  }
  std::cout << sum << std::endl;
  return 0;
}