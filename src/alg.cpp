// Copyright 2025 NNTU-CS
#include "alg.h"
#include "tstack.h"

#include <cctype>
#include <map>
#include <string>

bool isDigit(char c) {
  return std::isdigit(static_cast<unsigned char>(c));
}

std::string infx2pstfx(const std::string& inf) {
  TStack<char> stack;
  std::string result;

  std::map<char, int> priority;
  priority['+'] = 1;
  priority['-'] = 1;
  priority['*'] = 2;
  priority['/'] = 2;
  priority['('] = 0;

  int l = inf.length();

  for (int i = 0; i < l; ++i) {
    char c = inf[i];

    if (isDigit(c)) {
      while (i < l && isDigit(inf[i])) {
        result += inf[i];
        ++i;
      }
      result += ' ';
      --i;
    } else if (c == '(') {
      stack.push(c);
    } else if (c == ')') {
      while (!stack.isEmpty() && stack.get() != '(') {
        result += stack.get();
        result += ' ';
        stack.pop();
      }
      if (!stack.isEmpty() && stack.get() == '(') {
        stack.pop();
      }
    } else if (c == '+' || c == '-' || c == '*' || c == '/') {
      while (!stack.isEmpty() && priority[stack.get()] >= priority[c]) {
        result += stack.get();
        result += ' ';
        stack.pop();
      }
      stack.push(c);
    }
  }

  while (!stack.isEmpty()) {
    result += stack.get();
    result += ' ';
    stack.pop();
  }

  if (!result.empty() && result.back() == ' ') {
    result.pop_back();
  }

  return result;
}

int eval(const std::string& pref) {
  TStack<int> stack;
  std::string num;

  for (char c : pref) {
    if (isDigit(c)) {
      num += c;
    } else if (c == ' ' && !num.empty()) {
      stack.push(std::stoi(num));
      num.clear();
    } else if (c == '+' || c == '-' || c == '*' || c == '/') {
      int b = stack.get();
      stack.pop();
      int a = stack.get();
      stack.pop();

      int result = 0;
      switch (c) {
        case '+':
          result = a + b;
          break;
        case '-':
          result = a - b;
          break;
        case '*':
          result = a * b;
          break;
        case '/':
          result = a / b;
          break;
      }
      stack.push(result);
    }
  }

  return stack.get();
}
