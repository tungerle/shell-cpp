#include <iostream>
#include <string>
#include <set>
#include <cstdlib>
#include <sstream>
#include <vector>
#include <unistd.h>
#include <sys/types.h>
#include <cstring>
#include <sys/wait.h>

std::set<std::string> builtins = {"echo", "exit", "type", "pwd", "cd"};
int main() {

  // Flush after every std::cout / std:cerr
  std::cout << std::unitbuf;
  std::cerr << std::unitbuf;

  // store all directories in directories_split vector
  std::string path = std::getenv("PATH");
  std::stringstream directory_stream(path);
  std::string buffer;
  std::vector<std::string> directories_split;
  while(std::getline(directory_stream, buffer, ':')) {
    directories_split.push_back(buffer);
  }

  
  // get user's input
  while (true) {
    std::cout << "$ ";
    std::string input;
    std::getline(std::cin, input);

    //store input as a c-string in input_vector
    std::istringstream input_stream(input);
    std::vector<char*> input_vector; 
    while(input_stream >> buffer){
      input_vector.push_back(strdup(buffer.c_str()));
    }
    input_vector.push_back(nullptr);

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

      // search for command
      else { 
        for (int i=0; i < size(directories_split); i++){ 
          std::string command_path = directories_split[i]+ "/" + name;
          //check if command exists in PATH
          if (access(command_path.c_str(), X_OK) ==0) {
            std::cout << name + " is " + command_path <<std::endl;
            break;
          } 
          else if (i == size(directories_split) - 1){
            std::cout << name + ": not found" << std::endl;
          }
        }
      }
    }

    // pwd
    else if (input == "pwd"){
      char *cwd = getcwd(NULL, 0);

      std::cout << cwd << std::endl;
      free(cwd);
    }
    
    //cd
    else if (input.compare(0,3, "cd ") == 0){
      if (input.substr(3) == "~"){
        char *home = getenv("HOME");
        chdir(home);
      }
      else if (chdir(input_vector[1]) != 0){
        std::cout<< input.substr(3) + ": No such file or directory"<<std::endl;
      }
    }

    // look for non builtin command from path, start process
    else {
      bool found = false;
      char **argv = input_vector.data();
      for (auto &directory : directories_split){
          std::string command_path = directory + "/" + input_vector[0];
          if (access(command_path.c_str(), X_OK) == 0){
            found = true;
            pid_t pid = fork();
            if (pid == 0){
              execvp(argv[0], argv);
              perror("execvp failed");
              exit(1);
            } else if (pid > 0) {
              int status;
              waitpid(pid, &status, 0);
              break;
            }
          }
        }

      // path not found, invalid command
      if (found == false){
        std::cout << input << ": command not found" <<std::endl;
      }

    // free allocated memory from strdup
    for (char * allocated : input_vector){
        if (allocated != nullptr) {
          free(allocated);
        }
      }

    }

  } // end while loop

return 0;
}
