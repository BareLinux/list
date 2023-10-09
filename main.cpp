#include <iostream>
#include <filesystem>
#include <iomanip>
#include <sstream>
#include <vector>

namespace list = std::filesystem; // Updated namespace to 'list'

// ANSI escape codes for text colors
const std::string GREEN = "\x1B[32m";  // Green
const std::string DARK_BLUE = "\x1B[34m";  // Dark Blue
const std::string CYAN = "\x1B[36m";  // Cyan
const std::string RESET_COLOR = "\x1B[0m";  // Reset color to default

std::uintmax_t calculateDirectorySize(const list::path& directoryPath) { // Updated 'fs::path' to 'list::path'
    std::uintmax_t totalSize = 0;

    for (const auto& entry : list::recursive_directory_iterator(directoryPath)) { // Updated 'fs::recursive_directory_iterator' to 'list::recursive_directory_iterator'
        const list::path& path = entry.path(); // Updated 'fs::path' to 'list::path'

        if (list::is_regular_file(path)) { // Updated 'fs::is_regular_file' to 'list::is_regular_file'
            totalSize += list::file_size(path); // Updated 'fs::file_size' to 'list::file_size'
        }
    }

    return totalSize;
}

bool compareEntries(const list::directory_entry& entry1, const list::directory_entry& entry2) { // Updated 'fs::directory_entry' to 'list::directory_entry'
    if (entry1.is_directory() && !entry2.is_directory()) {
        return true;
    } else if (!entry1.is_directory() && entry2.is_directory()) {
        return false;
    } else {
        return entry1.path().filename() < entry2.path().filename();
    }
}

void listDirectoryContents(const list::path& directoryPath) { // Updated 'fs::path' to 'list::path'
    std::vector<list::directory_entry> entries; // Updated 'fs::directory_entry' to 'list::directory_entry'

    for (const auto& entry : list::directory_iterator(directoryPath)) { // Updated 'fs::directory_iterator' to 'list::directory_iterator'
        entries.push_back(entry);
    }

    std::sort(entries.begin(), entries.end(), compareEntries);

    for (const auto& entry : entries) {
        const list::path& path = entry.path(); // Updated 'fs::path' to 'list::path'
        std::string size;

        if (list::is_directory(path)) { // Updated 'fs::is_directory' to 'list::is_directory'
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
        } else if (list::is_regular_file(path)) { // Updated 'fs::is_regular_file' to 'list::is_regular_file'
            std::uintmax_t fileSize = list::file_size(path); // Updated 'fs::file_size' to 'list::file_size'
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
    list::path pathToList; // Updated 'fs::path' to 'list::path'

    if (argc == 1) {
        // No command-line arguments provided, list the current directory.
        pathToList = list::current_path(); // Updated 'fs::current_path' to 'list::current_path'
    } else if (argc == 2) {
        // Command-line argument provided, use it as the path to list.
        pathToList = argv[1];
    } else {
        std::cerr << "Usage: " << argv[0] << " [directory or file path]" << std::endl;
        return 1;
    }

    if (!list::exists(pathToList)) { // Updated 'fs::exists' to 'list::exists'
        std::cerr << "Path does not exist: " << pathToList.string() << std::endl;
        return 1;
    }

    std::cout << "Listing contents of: " << pathToList.string() << std::endl;

    if (list::is_directory(pathToList)) { // Updated 'fs::is_directory' to 'list::is_directory'
        listDirectoryContents(pathToList);
    } else if (list::is_regular_file(pathToList)) { // Updated 'fs::is_regular_file' to 'list::is_regular_file'
        std::uintmax_t fileSize = list::file_size(pathToList); // Updated 'fs::file_size' to 'list::file_size'
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
