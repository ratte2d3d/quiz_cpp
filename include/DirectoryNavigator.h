#include <string>
#include <vector>

class DirectoryNavigator
{
private:
    std::string currentPath;
    std::vector<std::pair<std::string, bool>> fileEntries; // ファイル名とタイプ

public:
    DirectoryNavigator(const std::string &startPath);
    ~DirectoryNavigator();

    std::string getCurrentPath(void);

    void readDirectory();
    bool selectFile();
};