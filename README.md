# My Custom C++ Shell

This is a minimal Unix-like shell written in modern C++ (C++2b), originally built as part of a Codecrafters challenge.

## Features
- Executes commands using `fork()` and `execvp()`
- PATH resolution for commands like `ls`, `echo`, etc.
- Simple tokenizer with space-based delimiters

## Build Instructions

Make sure you have `clang++` installed.

build manually: 

clang++ -std=c++2b -o my_shell main.cpp
