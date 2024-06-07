#include <string>
#include <vector>

class Dataset {
public:
    Dataset(std::string path);
    std::string get(int index);
private:
    std::vector<std::string> _paths;
    std::vector<std::string> _sort(std::vector<std::string>& filenames);
    static std::pair<int, int> extract_keys(const std::string& filename);
    static bool compare_filenames(const std::string& a, const std::string& b);
    std::vector<std::string> sort_filenames(std::vector<std::string>& filenames);
};