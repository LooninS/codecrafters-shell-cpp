#include <filesystem>
#include <iostream>
#include <string>
#include <vector>
#include <unistd.h>
namespace fs = std::filesystem;

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
      size_t start = 0;
      int found = 0;
      while (start<=path.size()) {
        size_t end = path.find(':', start);
        std::string dir = path.substr(start, end-start);
        std::string fullpath = dir + "/" + command;
        
        if (fs::exists(fullpath) && (fs::status(fullpath).permissions() & fs::perms::owner_exec) != fs::perms::none) {
              std::cout << command << " is "<<fullpath << std::endl;
              found = 1;
              break;
            }
        if (end == std::string::npos) break;
        start = end+1;
      }

      if (!found) {
        std::cout << command << ": not found" << std::endl;
      }

    }
    else {
      std::cout << input << ": not found" << std::endl;
  }
}
}


