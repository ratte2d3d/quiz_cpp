#include <iostream>
#include "DirectoryNavigator.h"

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        std::cerr << "How to use -> " << argv[0] << " <question dirname>" << std::endl;
        return 1;
    }

    DirectoryNavigator navigator(argv[1]); // カレントディレクトリから開始
    while (true)
    {
        navigator.readDirectory(); // ディレクトリの読み込み

        // ファイルの選択が完了したらループを抜ける
        if (navigator.selectFile())
        {
            break;
        };
    }

    std::cout << "Selected file : " << navigator.getCurrentPath() << std::endl;

    return 0;
}