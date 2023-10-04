# Directory Contents Listing Tool

This command-line application allows you to list the files and folders in a directory and display their sizes. It formats file sizes in megabytes (MB) for files smaller than 1024 MB and in gigabytes (GB) for files larger than or equal to 1024 MB. Additionally, it calculates and displays folder sizes.

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

2. Compile the program using a C++ compiler with C++17 support. For example, using `g++`:

   ```bash
   g++ -std=c++17 -o list_dir_contents list_directory_contents.cpp
