#include <iostream>
#include <filesystem>
#include <iomanip>
#include <sstream>
#include <vector> // Added for sorting

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

// Custom comparison function for sorting
bool compareEntries(const fs::directory_entry& entry1, const fs::directory_entry& entry2) {
    if (entry1.is_directory() && !entry2.is_directory()) {
        return true; // Directories come before files
    } else if (!entry1.is_directory() && entry2.is_directory()) {
        return false; // Files come after directories
    } else {
        return entry1.path().filename() < entry2.path().filename(); // Alphabetical sorting
    }
}

void listDirectoryContents(const fs::path& directoryPath) {
    std::vector<fs::directory_entry> entries;

    for (const auto& entry : fs::directory_iterator(directoryPath)) {
        entries.push_back(entry);
    }

    // Sort the entries using the custom comparison function
    std::sort(entries.begin(), entries.end(), compareEntries);

    for (const auto& entry : entries) {
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
            size = "N/A";
        }

        std::cout << path.filename().string() << " (" << size << ")" << std::endl;
    }
}

int main() {
    fs::path currentDirectory = fs::current_path();

    std::cout << "Current directory: " << currentDirectory.string() << std::endl;

    listDirectoryContents(currentDirectory);
    return 0;
}
