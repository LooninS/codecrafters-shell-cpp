#include <iostream>
#include <string>

int main() {
  // Flush after every std::cout / std:cerr
  std::cout << std::unitbuf;
  std::cerr << std::unitbuf;

  // TODO: Uncomment the code below to pass the first stage
  while (1) {
    std::cout << "$ ";
    std::string input;
    std::getline(std::cin, input);
    if (input.substr(0, 5) == "echo ") {
      std::cout << input.substr(5) << std::endl;
    }
    else if (input == "exit") break;
    else {
      std::cout << input << ": command not found" << std::endl;
    }


  }
}
