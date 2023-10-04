#include <iostream>
#include <filesystem>
#include <iomanip> // For std::setprecision and std::fixed
#include <sstream>

namespace fs = std::filesystem;

// Function to calculate the total size of files in a directory
std::uintmax_t calculateDirectorySize(const fs::path& directoryPath) {
    std::uintmax_t totalSize = 0;

    for (const auto& entry : fs::directory_iterator(directoryPath)) {
        const fs::path& path = entry.path();

        if (fs::is_regular_file(path)) {
            totalSize += fs::file_size(path);
        }
    }

    return totalSize;
}

void listDirectoryContents(const fs::path& directoryPath) {
    for (const auto& entry : fs::directory_iterator(directoryPath)) {
        const fs::path& path = entry.path();
        std::string size;

        if (fs::is_directory(path)) {
            std::uintmax_t dirSize = calculateDirectorySize(path);
            if (dirSize == 0) {
                size = "Empty Folder";
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
        } else {
            size = "N/A"; // Handle other types (symlinks, sockets, etc.)
        }

        std::cout << path.filename().string() << " (" << size << ")" << std::endl;
    }
}

int main() {
    fs::path currentDirectory = fs::current_path();

    std::cout << "Listing files and folders in the current directory: " << currentDirectory.string() << std::endl;

    listDirectoryContents(currentDirectory);
    return 0;
}
