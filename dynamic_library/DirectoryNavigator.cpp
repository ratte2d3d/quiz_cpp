
#include "DirectoryNavigator.h"
#include <dirent.h>
#include <iostream>
#include <string>
#include <vector>
#include <chrono>
#include <thread>
#include <cstdlib>

DirectoryNavigator::DirectoryNavigator(const std::string &startPath) : currentPath(startPath) {};

DirectoryNavigator::~DirectoryNavigator() {};

std::string DirectoryNavigator::getCurrentPath(void)
{
    return currentPath;
};

void DirectoryNavigator::readDirectory()
{

    DIR *dir = opendir(currentPath.c_str()); // ディレクトリを開く
    struct dirent *file;                     // dirent構造体のポインタ
    fileEntries.clear();

    // ディレクトリを開く
    while ((file = readdir(dir)) != nullptr)
    {
        if (file->d_name[0] != '.') // ドットで始まるファイルを除外
        {
            bool isDir = (file->d_type == DT_DIR);
            fileEntries.push_back({file->d_name, isDir}); // ファイル名とタイプを保存
        }
    }
};

bool DirectoryNavigator::selectFile()
{
    system("clear"); // コンソールをクリア
    std::cout << "\n=======================================================\n";
    std::cout << "Now Directory: " << currentPath << std::endl;
    std::cout << "=======================================================\n";

    // ディレクトリ内を表示
    for (int i = -1; i < static_cast<int>(fileEntries.size()); i++)
    {
        if (i == -1)
            std::cout << i + 1 << ": Back(..)" << std::endl;
        else
            std::cout << i + 1 << ": " << fileEntries[i].first << std::endl;
    }

    // ファイル番号を入力
    int fileNum = 0;
    std::cout << "Please input number to open >> ";
    std::cin >> fileNum;
    fileNum--; // 0から始まるインデックスに変換

    // 入力値のチェック
    if (fileNum < -1 || static_cast<int>(fileEntries.size()) < fileNum)
    {
        std::cout << "Out of range. Please try again." << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
    else if (fileNum == -1)
    {
        currentPath = currentPath + "/..";
    }
    else
    {
        currentPath = currentPath + "/" + fileEntries[fileNum].first;
    }

    // ファイルが選択された場合はtrueを返す
    return fileEntries[fileNum].second ? false : true;
};