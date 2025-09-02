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

  else if (input.compare(0, 5, "echo ") == 0){
    std::cout <<input.substr(5) <<std::endl;
  }

  else if (input.compare(0, 4, "type") == 0) {
    if (input == "type echo") {
      std::cout << "echo is a shell builtin" <<std::endl;
    }
    else if (input == "type exit"){
      std::cout<< "exit is a shell builtin" <<std::endl;
    }
    else if (input == "type type"){
      std::cout<< "type is a shell builtin" <<std::endl;
    }

  else {
  std::cout << input << ": command not found" <<std::endl;
  }

} // end While loop

return 0;
}
