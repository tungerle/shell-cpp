#include <iostream>
#include <string>
#include <set>
#include <cstdlib>
#include <sstream>
#include <vector>
#include <unistd.h>

std::set<std::string> builtins = {"echo", "exit", "type"};
int main() {


  // Flush after every std::cout / std:cerr
  std::cout << std::unitbuf;
  std::cerr << std::unitbuf;
  std::string path = std::getenv("PATH");
  std::stringstream directory_stream(path);
  std::string buffer;
  std::vector<std::string> directories_split;

  while(std::getline(directory_stream, buffer, ':')) {
    directories_split.push_back(buffer);
  }


  while (true) {
  std::cout << "$ ";
  std::string input;
  std::getline(std::cin, input);

  // exit
  if (input == "exit 0"){
    break;
  }
  // echo
  else if (input.compare(0, 5, "echo ") == 0){
    std::cout <<input.substr(5) <<std::endl;
  }
  // type
  else if (input.compare(0, 5, "type ") == 0) {
    std::string name = input.substr(5);
    if (builtins.count(name)) {
      std::cout << name << " is a shell builtin" <<std::endl;
    }
    // search path for command
    else { 
      for (int i=0; i< size(directories_split); i++){ 
        std::string current_path = directories_split[i]+ "/" + name;
        // exists
        if (access(current_path.c_str(), X_OK) ==0) {
          std::cout << name + " is " + current_path <<std::endl;
          break;
        } 
        else if (i == size(directories_split) - 1){
          std::cout << name + ": not found" << std::endl;
          }
      }
    }
  }
  // invalid command
  else {
  std::cout << input << ": command not found" <<std::endl;
    }
  } // end while loop
return 0;
}
