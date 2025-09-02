#include <iostream>
#include <string>

int main() {
  // Flush after every std::cout / std:cerr
  std::cout << std::unitbuf;
  std::cerr << std::unitbuf;

  while (true) {

  std::cout << "$ ";

  std::string input;
  std::getline(std::cin, input);
  if (input == "exit 0"){
    break;
  }
  if (input.starts_with("echo", 0) == 0){
    std::cout <<input.substr(5) <<std::endl;
  }
  std::cout << input << ": command not found" <<std::endl;
  }
  return 0;
}
