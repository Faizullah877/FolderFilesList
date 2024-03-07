#include <iostream>
#include <vector>
#include <string>
#include <algorithm> // For std::transform
#include <cstring>   // For std::strcmp

#ifdef WIN32
#include <windows.h> // For Windows-specific directory handling
#else
#include <dirent.h>  // For POSIX directory handling
#endif

// Helper function to check if a file has a specific extension
bool has_extension(const std::string& filename, const std::string& ext) {
    size_t pos = filename.find_last_of('.');
    if (pos != std::string::npos) {
        std::string file_ext = filename.substr(pos + 1);
        std::transform(file_ext.begin(), file_ext.end(), file_ext.begin(), ::tolower);
        return (file_ext == ext);
    }
    return false;
}

// Function to get files in a directory with specific extensions
std::vector<std::string> get_files_in_directory(const std::string& directory) {
    std::vector<std::string> file_paths;

#ifdef WIN32
    // Windows-specific code
    WIN32_FIND_DATA file_data;
    HANDLE dir = FindFirstFile((directory + "\\*").c_str(), &file_data);
    if (dir != INVALID_HANDLE_VALUE) {
        do {
            if (file_data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
                continue; // Skip directories
            std::string filename = file_data.cFileName;
            if (has_extension(filename, "jpg") || has_extension(filename, "jpeg") || has_extension(filename, "jumbf")) {
                file_paths.push_back(directory + "\\" + filename);
            }
        } while (FindNextFile(dir, &file_data));
        FindClose(dir);
    }
#else
    // POSIX (Linux) code
    DIR* dir = opendir(directory.c_str());
    if (dir) {
        struct dirent* entry;
        while ((entry = readdir(dir)) != nullptr) {
            if (entry->d_type == DT_REG) { // Regular file
                std::string filename = entry->d_name;
                if (has_extension(filename, "jpg") || has_extension(filename, "jpeg") || has_extension(filename, "jumbf")) {
                    file_paths.push_back(directory + "/" + filename);
                }
            }
        }
        closedir(dir);
    }
#endif

    return file_paths;
}

int main() {
    std::string directory_path = "E:/Dev/Dbench_JPEG_Systems/JUMBF_reference_dataset_DISv2/files";
    std::vector<std::string> files = get_files_in_directory(directory_path);

    std::cout << "Files with specified extensions in directory " << directory_path << ":\n";
    for (const auto& file : files) {
        std::cout << file << std::endl;
    }

    return 0;
}
