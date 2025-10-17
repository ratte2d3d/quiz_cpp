#include <iostream>
#include "include/DirectoryNavigator.h"
#include "include/QuizManager.h"
#include "include/QuizIO.h"

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
    QuizIO quizIO;

    if (quizIO.loadCSV(navigator.getCurrentPath(), quiz)){

        quiz.display();

        while (quiz.startQuiz()){
            quizIO.saveCSV(navigator.getCurrentPath(), quiz);
            quiz.display();
        }
        
        quizIO.saveCSV(navigator.getCurrentPath(), quiz);
    }

    return 0;
}