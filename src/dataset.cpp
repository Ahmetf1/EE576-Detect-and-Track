#include <dataset.h>
#include <filesystem>
#include <algorithm>
#include <regex>
#include <climits>

// Read all the image paths from the folder
Dataset::Dataset(std::string path) {
    for (const auto & entry : std::filesystem::directory_iterator(path)) {
        _paths.push_back(entry.path().string());
    }
    _paths = _sort(_paths);
}

std::string Dataset::get(int index) {
    return _paths[index];
}

// Function to extract sorting keys from the filename
std::pair<int, int> Dataset::extract_keys(const std::string& filename) {
    std::regex pattern(R"(kitchen_small_(\d+)_(\d+)\.png)");
    std::smatch match;
    if (std::regex_search(filename, match, pattern)) {
        return {std::stoi(match[1]), std::stoi(match[2])};
    } else {
        return {INT_MAX, INT_MAX}; // In case the filename doesn't match the pattern
    }
}

// Comparator function for sorting filenames
bool Dataset::compare_filenames(const std::string& a, const std::string& b) {
    auto key_a = extract_keys(a);
    auto key_b = extract_keys(b);
    return key_a < key_b;
}

// Function to sort filenames
std::vector<std::string> Dataset::_sort(std::vector<std::string>& filenames) {
    std::sort(filenames.begin(), filenames.end(), &Dataset::compare_filenames);
    return filenames;
}