#include <iostream>
#include "include/DirectoryNavigator.h"
#include "include/QuizManager.h"

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

    QuizManager quiz;
    quiz.newNode("a", "b", "input");
    quiz.newNode("c", "d", "choice.2");
    quiz.newNode("e", "f", "choice.1");
    quiz.newNode("g", "h", "choice.0");
    quiz.deleteNode(1);
    quiz.display();
    quiz.deleteNode(3);
    quiz.display();
    quiz.deleteNode(2);
    quiz.display();
    quiz.deleteNode(1);
    quiz.display();

    return 0;
}