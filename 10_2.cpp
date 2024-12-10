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

struct Position {
  int x;
  int y;
  Position(int x, int y) : x(x), y(y) {}
  bool isValid(int limit) const {
    return x >= 0 && x <= limit && y >= 0 && y <= limit;
  }
};

struct Node {
  Position position;
  char value = 0;
  Node *parent;
  bool visited = false;
  std::vector<Node *> chilren;
  Node() : position(-1, -1), parent(nullptr) {}
  Node(Position pos) : position(pos), parent(nullptr) {}
  Node(Position pos, Node *par, char v)
      : position(pos), parent(par), value(v) {}
};

void buildGraph(Node *head, std::vector<std::string> &lines) {
  if (head == nullptr) {
    return;
  }
  int headValue = lines[head->position.x][head->position.y] - '0';
  Position leftPosition(head->position.x, head->position.y - 1);
  Position rightPosition(head->position.x, head->position.y + 1);
  Position topPosition(head->position.x - 1, head->position.y);
  Position bottomPosition(head->position.x + 1, head->position.y);
  if (leftPosition.isValid(lines.size() - 1) &&
      lines[leftPosition.x][leftPosition.y] == headValue + 1 + '0') {
    head->chilren.push_back(
        new Node(leftPosition, head, lines[leftPosition.x][leftPosition.y]));
    /*if (lines[leftPosition.x][leftPosition.y] == '9') {
      lines[leftPosition.x][leftPosition.y] = '.';
    }*/
  }
  if (rightPosition.isValid(lines.size() - 1) &&
      lines[rightPosition.x][rightPosition.y] == headValue + 1 + '0') {
    head->chilren.push_back(
        new Node(rightPosition, head, lines[rightPosition.x][rightPosition.y]));
    /*if (lines[rightPosition.x][rightPosition.y] == '9') {
      lines[rightPosition.x][rightPosition.y] = '.';
    }*/
  }
  if (topPosition.isValid(lines.size() - 1) &&
      lines[topPosition.x][topPosition.y] == headValue + 1 + '0') {
    head->chilren.push_back(
        new Node(topPosition, head, lines[topPosition.x][topPosition.y]));
    /*if (lines[topPosition.x][topPosition.y] == '9') {
      lines[topPosition.x][topPosition.y] = '.';
    }*/
  }
  if (bottomPosition.isValid(lines.size() - 1) &&
      lines[bottomPosition.x][bottomPosition.y] == headValue + 1 + '0') {
    head->chilren.push_back(new Node(
        bottomPosition, head, lines[bottomPosition.x][bottomPosition.y]));
    /*if (lines[bottomPosition.x][bottomPosition.y] == '9') {
      lines[bottomPosition.x][bottomPosition.y] = '.';
    }*/
  }
  for (auto child : head->chilren) {
    buildGraph(child, lines);
  }
}

int trailheadCount(Node *head) {
  int sum = 0;
  if (head->chilren.size() == 0 && head->value == '9') {
    return 1;
  }
  for (auto child : head->chilren) {
    sum += (trailheadCount(child));
  }
  return sum;
}

int main() {
  std::ifstream in("input.txt");
  std::string line;
  std::vector<std::string> lines;
  unsigned long long trailheadScore = 0;
  unsigned long long trailheadScoreSum = 0;
  unsigned long long trailheadCounter = 0;

  while (std::getline(in, line)) {
    lines.push_back(line);
  }
  for (int i = 0; i < lines.size(); i++) {
    for (int j = 0; j < lines[i].size(); j++) {
      if (lines[i][j] == '0') {
        Node head(Position(i, j));
        std::vector<std::string> lines2 = lines;
        buildGraph(&head, lines2);
        std::cout << "end of buildGraph" << std::endl;
        trailheadScore = trailheadCount(&head);
        if (trailheadScore) {
          trailheadCounter++;
        }
        trailheadScoreSum += trailheadScore;
      }
    }
  }

  std::cout << "score:" << trailheadScoreSum << " sum:" << trailheadCounter
            << std::endl;
  return 0;
}