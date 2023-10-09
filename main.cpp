#include <iostream>
#include <filesystem>
#include <iomanip>
#include <sstream>
#include <vector>

namespace fs = std::filesystem;

// ANSI escape codes for text colors
const std::string GREEN = "\x1B[32m";  // Green
const std::string DARK_BLUE = "\x1B[34m";  // Dark Blue
const std::string CYAN = "\x1B[36m";  // Cyan
const std::string RESET_COLOR = "\x1B[0m";  // Reset color to default

std::uintmax_t calculateDirectorySize(const fs::path& directoryPath) {
    std::uintmax_t totalSize = 0;

    for (const auto& entry : fs::recursive_directory_iterator(directoryPath)) {
        const fs::path& path = entry.path();

        if (fs::is_regular_file(path)) {
            totalSize += fs::file_size(path);
        }
    }

    return totalSize;
}

bool compareEntries(const fs::directory_entry& entry1, const fs::directory_entry& entry2) {
    if (entry1.is_directory() && !entry2.is_directory()) {
        return true;
    } else if (!entry1.is_directory() && entry2.is_directory()) {
        return false;
    } else {
        return entry1.path().filename() < entry2.path().filename();
    }
}

void listDirectoryContents(const fs::path& directoryPath) {
    std::vector<fs::directory_entry> entries;

    for (const auto& entry : fs::directory_iterator(directoryPath)) {
        entries.push_back(entry);
    }

    std::sort(entries.begin(), entries.end(), compareEntries);

    for (const auto& entry : entries) {
        const fs::path& path = entry.path();
        std::string size;

        if (fs::is_directory(path)) {
            std::uintmax_t dirSize = calculateDirectorySize(path);
            if (dirSize == 0) {
                size = "Empty";
            } else if (dirSize < 1024 * 1024) {
                size = std::to_string(dirSize / 1024) + " KB";
            } else if (dirSize < 1024 * 1024 * 1024) {
                double sizeInMB = static_cast<double>(dirSize) / (1024 * 1024);
                std::ostringstream ss;
                ss << std::fixed << std::setprecision(2) << sizeInMB << " MB";
                size = ss.str();
            } else {
                double sizeInGB = static_cast<double>(dirSize) / (1024 * 1024 * 1024);
                std::ostringstream ss;
                ss << std::fixed << std::setprecision(2) << sizeInGB << " GB";
                size = ss.str();
            }

            // Color code for folders (dark blue)
            std::cout << DARK_BLUE << path.filename().string() << RESET_COLOR << " (" << size << ")" << std::endl;
        } else if (fs::is_regular_file(path)) {
            std::uintmax_t fileSize = fs::file_size(path);
            if (fileSize < 1024 * 1024) {
                size = std::to_string(fileSize / 1024) + " KB";
            } else if (fileSize < 1024 * 1024 * 1024) {
                double sizeInMB = static_cast<double>(fileSize) / (1024 * 1024);
                std::ostringstream ss;
                ss << std::fixed << std::setprecision(2) << sizeInMB << " MB";
                size = ss.str();
            } else {
                double sizeInGB = static_cast<double>(fileSize) / (1024 * 1024 * 1024);
                std::ostringstream ss;
                ss << std::fixed << std::setprecision(2) << sizeInGB << " GB";
                size = ss.str();
            }

            // Color code for files (cyan)
            std::cout << CYAN << path.filename().string() << RESET_COLOR << " (" << size << ")" << std::endl;
        } else {
            size = "N/A";

            // Color code for executables (green)
            std::cout << GREEN << path.filename().string() << RESET_COLOR << " (" << size << ")" << std::endl;
        }
    }
}

int main(int argc, char* argv[]) {
    fs::path pathToList;

    if (argc == 1) {
        // No command-line arguments provided, list the current directory.
        pathToList = fs::current_path();
    } else if (argc == 2) {
        // Command-line argument provided, use it as the path to list.
        pathToList = argv[1];
    } else {
        std::cerr << "Usage: " << argv[0] << " [directory or file path]" << std::endl;
        return 1;
    }

    if (!fs::exists(pathToList)) {
        std::cerr << "Path does not exist: " << pathToList.string() << std::endl;
        return 1;
    }

    std::cout << "Listing contents of: " << pathToList.string() << std::endl;

    if (fs::is_directory(pathToList)) {
        listDirectoryContents(pathToList);
    } else if (fs::is_regular_file(pathToList)) {
        std::uintmax_t fileSize = fs::file_size(pathToList);
        std::string size;

        if (fileSize < 1024 * 1024) {
            size = std::to_string(fileSize / 1024) + " KB";
        } else if (fileSize < 1024 * 1024 * 1024) {
            double sizeInMB = static_cast<double>(fileSize) / (1024 * 1024);
            std::ostringstream ss;
            ss << std::fixed << std::setprecision(2) << sizeInMB << " MB";
            size = ss.str();
        } else {
            double sizeInGB = static_cast<double>(fileSize) / (1024 * 1024 * 1024);
            std::ostringstream ss;
            ss << std::fixed << std::setprecision(2) << sizeInGB << " GB";
            size = ss.str();
        }

        // Color code for files (cyan)
        std::cout << CYAN << "File: " << pathToList.filename().string() << RESET_COLOR << " (" << size << ")" << std::endl;
    } else {
        std::cerr << "Invalid path type: " << pathToList.string() << std::endl;
        return 1;
    }

    return 0;
}
