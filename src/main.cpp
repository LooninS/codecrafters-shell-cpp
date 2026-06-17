#include <filesystem>
#include <iostream>
#include <string>
#include <vector>

int main() {
  // Flush after every std::cout / std:cerr
  std::cout << std::unitbuf;
  std::cerr << std::unitbuf;

  // TODO: Uncomment the code below to pass the first stage
  std::vector<std::string> args ={"echo", "exit", "type"};
  while (1) {
    std::cout << "$ ";
    std::string input;
    std::getline(std::cin, input);
    if (input.substr(0, 5) == "echo ") {
      std::cout << input.substr(5) << std::endl;
    }
    else if (input == "exit") break;
    else if (input.substr(0, 5) == "type ") {
      std::string command = input.substr(5);
      for (auto &arg : args) {
        if (arg == command) {
          std::cout << command << " is a shell builtin" << std::endl;
          break;
        }
      }
      std::string path = getenv("PATH");
      std::filesystem::path p(path);
      for (auto &entry : std::filesystem::directory_iterator(p)) {
        if (entry.path().filename() == command) {
          std::cout << input.substr(5) << " is " <<entry.path() << std::endl;
          break;
        }
      }
    }
  }
}


