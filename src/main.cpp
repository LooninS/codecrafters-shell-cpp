#include <filesystem>
#include <iostream>
#include <string>
#include <vector>
#include <unistd.h>
namespace fs = std::filesystem;
std::vector<std::string> split(const std::string& s, char delim) {
    std::vector<std::string> parts;
    size_t start = 0, end = s.find(delim);

    while (end != std::string::npos) {
        parts.push_back(s.substr(start, end - start));
        start = end + 1;
        end = s.find(delim, start);
    }
    parts.push_back(s.substr(start));
    return parts;
}

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
      int found = 0;
      for (auto &arg : args) {
        if (arg == command) {
          std::cout << command << " is a shell builtin" << std::endl;
          found = 1;
          break;
        }
      }

      if (!found) {
      std::string path = getenv("PATH");
      int found = 0;
      std::vector<std::string> paths = split(path, ':');
      for (auto &path : paths) {
        std::string fullpath = path + "/" + command;
        
        if (fs::exists(fullpath) && (fs::status(fullpath).permissions() & fs::perms::owner_exec) != fs::perms::none) {
              std::cout << command << " is "<<fullpath << std::endl;
              found = 1;
              break;
        }
      }

      if (!found) {
        std::cout << command << ": not found" << std::endl;
      }
    }

    }
    else {
      std::vector<std::string> commands = split(input, ' ');
      std::string command = commands[0];
      std::string path = getenv("PATH");
      int found = 0;
      std::vector<std::string> paths = split(path, ':');
      for (auto &path : paths) {
        std::string fullpath = path + "/" + command;
        
        if (fs::exists(fullpath) && (fs::status(fullpath).permissions() & fs::perms::owner_exec) != fs::perms::none) {
              system(input.c_str());
              found = 1;
              break;
        }
      }

      if (!found) {
        std::cout << command << ": not found" << std::endl;
      }

  }
 }
}


