#include "Tools.h"

using namespace std;

int Tools::getRandomNumber(int desde, int hasta) {
  default_random_engine gen(random_device{}());
  uniform_int_distribution<int> dist(desde, hasta);

  return dist(gen);
}

string Tools::selectRandomElement(const vector<string> &elements) {
  default_random_engine gen(random_device{}());
  uniform_int_distribution<int> dist(0, elements.size() - 1);

  return elements[dist(gen)];
}

vector<string> Tools::splitString(string &str, char delimiter) {
  vector<string> tokens;
  string token;
  istringstream tokenStream(str);

  while (getline(tokenStream, token, delimiter))
    tokens.push_back(token);

  return tokens;
}
