#include <algorithm>
#include <cmath>
#include <fstream>
#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <vector>

// # todo
// Instead of sorting by value, sort by percentage.

namespace CountLetters {

static std::map<char, float> countCharsInString(const std::string& str) {
  std::map<char, float> outcome;

  for (const char& c : str) {
    outcome[c]++;
  }
  return outcome;
}

static std::map<char, float> countUniqueChars(std::ifstream& incoming) {
  std::map<char, float> outcome;

  std::string line = "";
  while (getline(incoming, line)) {
    auto count = countCharsInString(line);
    // add the read chars and their value to outcome
    for (const auto& pair : count) {
      outcome[pair.first] += pair.second;
    }
  }

  return outcome;
}

};  // namespace CountLetters

namespace Display {

template <typename First, typename Second>
static std::string createCharFloatRow(First key, Second value) {
  std::stringstream row;

  row << '[' << key << "] "
      << std::string(static_cast<int>(std::round(value)), '=') << " - "
      << value;
  return row.str();
}

static float getPercentageFromTotal(float value, float total) {
  return (value * 100) / total;
}

template <typename T>
static void hotizontalBarChart(T& data) {
  std::stringstream out;

  for (const auto& pair : data) {
    out << createCharFloatRow(pair.first, pair.second) << '\n';
  }

  std::cout << out.str();
}

template <typename T>
static std::vector<std::pair<char, float>> sortByValue(T& charMap) {
  std::vector<std::pair<char, float>> vec(charMap.begin(), charMap.end());

  sort(vec.begin(), vec.end(),
       [](auto& a, auto& b) { return a.second > b.second; });

  return vec;
}

static std::vector<std::pair<char, float>> sortByProcent(
    std::map<char, float>& charMap, int decimal) {
  std::vector<std::pair<char, float>> vec(charMap.begin(), charMap.end());

  float total = 0;
  for (int i = 0; i < vec.size(); i++) {
    total += vec[i].second;
  }

  for (int i = 0; i < vec.size(); i++) {
    float procent = getPercentageFromTotal(vec[i].second, total);
    vec[i].second =
        std::round(procent * std::pow(10, decimal)) / std::pow(10, decimal);
  }

  vec = sortByValue(vec);

  return vec;
}

}  // namespace Display

int main(int argc, char* argv[]) {
  std::ifstream file;

  for (int i = 0; i < argc; i++) {
    if (argc == 1) {
      file.open("test.txt");
      std::cout << "Opened test.txt because no file was specified\n";
    } else {
      file.open(argv[i]);
    }

    if (!file.is_open()) {
      std::cerr << "File \'" << argv[i] << "\' did not open.\n";
      continue;
    }

    auto counted = CountLetters::countUniqueChars(file);
    auto sorted = Display::sortByProcent(counted, 10);
    Display::hotizontalBarChart(sorted);
    std::cout << "-------------------------------------------";
    file.close();
  }
  return 0;
}
