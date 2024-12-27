#include <fstream>
#include <integer.h>
#include <iostream>
#include <numeric>
#include <optional>
#include <regex>
#include <sstream>
#include <string>
#include <utility>
#include <vector>

std::vector<std::string> split(const std::string &s, char delimiter) {
  std::vector<std::string> tokens;
  std::string token;
  std::istringstream tokenStream(s);
  while (std::getline(tokenStream, token, delimiter)) {
    tokens.push_back(token);
  }
  return tokens;
}

struct linearEquation {
  CryptoPP::Integer x;
  CryptoPP::Integer y;
  CryptoPP::Integer c;

  linearEquation(CryptoPP::Integer x, CryptoPP::Integer y, CryptoPP::Integer c)
      : x(x), y(y), c(c) {}
  linearEquation operator-(const linearEquation &other) {
    return linearEquation(x - other.x, y - other.y, c - other.c);
  }
  linearEquation operator*(const CryptoPP::Integer &k) {
    return linearEquation(x * k, y * k, c * k);
  }
};

std::optional<std::pair<CryptoPP::Integer, CryptoPP::Integer>>
solve(linearEquation eq1, linearEquation eq2) {
  CryptoPP::Integer GCD = CryptoPP::Integer::Gcd(eq1.x, eq2.x);
  auto meq1 = eq1 * (eq2.x.DividedBy(GCD));
  auto meq2 = eq2 * (eq1.x.DividedBy(GCD));
  auto diffeq = meq1 - meq2;
  if (meq1.y < meq2.y) {
    diffeq = meq2 - meq1;
  }
  if (diffeq.y == 0) {
    std::cout << "diffeq.y == 0" << std::endl;
  }
  if (diffeq.c.Modulo(diffeq.y).IsZero()) {
    CryptoPP::Integer y = diffeq.c.DividedBy(diffeq.y);
    CryptoPP::Integer x =
        (eq1.c - CryptoPP::Integer(eq1.y * y)).DividedBy(eq1.x);
    if ((eq1.c - CryptoPP::Integer(eq1.y * y)).Modulo(eq1.x).IsZero()) {
      return std::make_pair(x, y);
    }
  }

  return std::nullopt;
}

int main(int, char const **) {
  CryptoPP::Integer counter = 0;
  std::ifstream input("input.txt");
  std::string line;
  int lineCounter = 0;
  std::string eq1;
  std::string eq2;
  std::string result;

  while (std::getline(input, line)) {
    switch (++lineCounter % 4) {
    case 1:
      eq1 = line;
      break;
    case 2:
      eq2 = line;
      break;
    case 3:
      result = line;
      break;
    case 0:
      std::regex re("x\\+\\d+");
      std::string tmp1 = split(eq1, ':')[1];
      std::string tmp2 = split(tmp1, ',')[0];
      std::string tmp3 = split(tmp1, ',')[1];
      std::string eq1x = split(tmp2, '+')[1];
      std::string eq1y = split(tmp3, '+')[1];

      std::string tmp21 = split(eq2, ':')[1];
      std::string tmp22 = split(tmp21, ',')[0];
      std::string tmp23 = split(tmp21, ',')[1];
      std::string eq2x = split(tmp22, '+')[1];
      std::string eq2y = split(tmp23, '+')[1];

      std::string tmpr1 = split(result, ':')[1];
      std::string tmpr2 = split(tmpr1, ',')[0];
      std::string tmpr3 = split(tmpr1, ',')[1];
      std::string resx = split(tmpr2, '=')[1];
      std::string resy = split(tmpr3, '=')[1];
      linearEquation equation1(CryptoPP::Integer(eq1x.c_str()),
                               CryptoPP::Integer(eq2x.c_str()),
                               CryptoPP::Integer(resx.c_str()));
      linearEquation equation2(CryptoPP::Integer(eq1y.c_str()),
                               CryptoPP::Integer(eq2y.c_str()),
                               CryptoPP::Integer(resy.c_str()));
      equation1.c += CryptoPP::Integer(10000000000000);
      equation2.c += CryptoPP::Integer(10000000000000);

      auto eqresult = solve(equation1, equation2);
      if (eqresult.has_value()) {
        // if (eqresult.value().first <= 100 && eqresult.value().second <= 100)
        // {
        counter += eqresult.value().first * 3 + eqresult.value().second;
        std::cout << eqresult.value().first << " " << eqresult.value().second
                  << std::endl;
        //}
      }
      break;
    }
  }
  input.close();

  std::cout << counter << std::endl;
  return 0;
}
