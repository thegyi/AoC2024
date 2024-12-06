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

struct position {
  int x;
  int y;
  position(int x, int y) : x(x), y(y) {}
  bool operator==(const position &other) const {
    return x == other.x && y == other.y;
  }

  bool operator<(const position &other) const {
    return x != other.x || y != other.y;
  }

  position operator+(const position &other) const {
    return position(x + other.x, y + other.y);
  }

  position operator-(const position &other) const {
    return position(x - other.x, y - other.y);
  }

  bool isValid(std::vector<std::string> &lines) {
    return x >= 0 && x < lines.size() && y >= 0 && y < lines[x].size();
  }
};

enum Direction { LEFT, RIGHT, UP, DOWN };

position findPosition(std::vector<std::string> &lines, const char c = '^') {
  for (int i = 0; i < lines.size(); i++) {
    for (int j = 0; j < lines[i].size(); j++) {
      if (lines[i][j] == c) {
        return position(i, j);
      }
    }
  }
  return position(-1, -1);
}
bool step(std::vector<std::string> &lines, position &pos, Direction &dir) {

  switch (dir) {
  case LEFT:
    if (pos.y == 0) {
      return false;
    } else {
      if (lines[pos.x][pos.y - 1] == '#') {
        dir = UP;
      } else {
        lines[pos.x][pos.y] = 'X';
        pos.y--;
        lines[pos.x][pos.y] = '^';
      }
    }
    break;
  case RIGHT:
    if (pos.y == lines[pos.x].size() - 1) {
      return false;
    } else {
      if (lines[pos.x][pos.y + 1] == '#') {
        dir = DOWN;
      } else {
        lines[pos.x][pos.y] = 'X';
        pos.y++;
        lines[pos.x][pos.y] = '^';
      }
    }
    break;
  case UP:
    if (pos.x == 0) {
      return false;
    } else {
      if (lines[pos.x - 1][pos.y] == '#') {
        dir = RIGHT;
      } else {
        lines[pos.x][pos.y] = 'X';
        pos.x--;
        lines[pos.x][pos.y] = '^';
      }
    }
    break;
  case DOWN:
    if (pos.x == lines.size() - 1) {
      return false;
    } else {
      if (lines[pos.x + 1][pos.y] == '#') {
        dir = LEFT;
      } else {
        lines[pos.x][pos.y] = 'X';
        pos.x++;
        lines[pos.x][pos.y] = '^';
      }
    }
    break;
  }
  return true;
}

int main() {
  std::ifstream in("6.txt");
  std::string line;
  std::vector<std::string> lines;
  unsigned long long count = 0;
  while (std::getline(in, line)) {
    lines.push_back(line);
  }
  position pos = findPosition(lines);
  Direction dir = UP;
  while (step(lines, pos, dir)) {
    pos = findPosition(lines);
  }
  for (const std::string &s : lines) {
    count += std::ranges::count(s, 'X');
  }
  std::cout << ++count << std::endl;
  return 0;
}
