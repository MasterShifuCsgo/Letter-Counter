#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include <sstream>
#include <algorithm>
#include <vector>
/*
1. what is argc and *argv[]. how does 'char *argv[]' give a string? explain how C++ sees it
2. 
*/

// what is this error in countUnique chars where the function is_open() is not available 2. it was istream not ifstream lol.

// # might todo
// 1. add argv and argc to main for the user to name the file in the terminal they want to read. enable reading through different trajectores as well
// 2. 


namespace CountLetters
{

  namespace {

    std::map<char, int> countCharsInString(const std::string& str) {
      std::map<char, int> outcome;;

      for (const char& c : str) {
        outcome[c]++;
      }
      return outcome;

    }
  }

  std::map<char, int> countUniqueChars(std::ifstream& incoming) {


    std::map<char, int> outcome;

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



};

namespace Display {

  namespace {

    std::string createCharIntRow(char key, int value) {
      std::stringstream row;      

      row << '[' << key << "] " << std::string(value, '*');
      return row.str();
    }
  }

template<typename T>
static void displayCharInt(T& data) {    
  std::stringstream out;

  for (const auto& pair : data) {
    out << createCharIntRow(pair.first, pair.second) << '\n';       
  }
      
  std::cout << out.str();
}

static std::vector<std::pair<char, int>> sortByValue(std::map<char, int>& charMap) {
  std::vector<std::pair<char, int>> vec(charMap.begin(), charMap.end());

  sort(vec.begin(), vec.end(), [](auto& a, auto& b) {
    return a.second > b.second;
    });

  return vec;
}

}

int main(int argc, char* argv[])
{
  
  std::ifstream file("test.txt"); 

  if (!file.is_open()) {
    std::cerr << "File did not open";
    return 1;
  }
 
  auto counted = CountLetters::countUniqueChars(file);  
  auto sorted = Display::sortByValue(counted);
  Display::displayCharInt(sorted);

  return 0;
}
