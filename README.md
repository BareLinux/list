# Directory Contents Listing Tool

Command Line c++ application to list folder and file size. "(ls)" and "(du)" command on steroids.

## Table of Contents

- [Requirements](#requirements)
- [Installation](#installation)
- [Usage](#usage)
- [Example](#example)
- [License](#license)

## Requirements

- A C++ compiler with C++17 support.
- The `<filesystem>` header, available in C++17 and later.

## Installation

1. Clone the repository or download the source code.

2. Compile the program using a C++ compiler with C++17 support on Linux. For example, using `g++`:

   ```bash
   g++ -std=c++17 -o list main.cpp

## Usage
 1. Running the program:
    ```bash
    ./list
 2. if you copy it to /bin or add it to your path:
    ```bash
    list

## Example

Listing files and folders in the current directory: /path/to/my_directory

file1.txt (2.45 MB)

file2.txt (158 KB)

subfolder (1.24 GB)

empty_folder (Empty Folder)

<br>
<img src="https://imgur.com/ADG5hxc">

## License

MIT License

Copyright (c) 2023 BareLinux

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS," WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.


