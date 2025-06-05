#include "../include/QuizManager.h"
#include <string>
#include <iostream>

QuizManager::QuizManager()
{
    root->next = nullptr;
};

QuizManager::~QuizManager() {};

// 末尾に新規ノードを作成
void QuizManager::newNode(std::string question, std::string answer, std::string format)
{
    // 新規ノードquizを作成
    quizzes *quiz = new quizzes();
    quiz->question = question;
    quiz->answer = answer;
    quiz->format = format;
    quiz->next = nullptr;

    // 末尾をquizに変更
    quizzes *ptr = root;
    while (ptr->next)
        ptr = ptr->next;
    ptr->next = quiz;
};

// 指定したindexのノードを削除
void QuizManager::deleteNode(int num)
{
    quizzes *ptr = root->next;
    quizzes *prev = nullptr;

    num--; // 指定したindex
    for (int i = 0; i < num; i++)
    {
        prev = ptr;      // 指定のひとつ前のノード
        ptr = ptr->next; // 指定したノード
    }

    if (num == 0) // 先頭を削除する場合
        root->next = ptr->next;
    else
        prev->next = ptr->next;

    delete ptr;
};

// リスト構造体を表示
void QuizManager::display()
{
    quizzes *ptr = root->next;
    int i = 1;

    // system("clear"); // コンソールをクリア
    std::cout << "---------------------------------------------------------------------------" << std::endl;
    while (ptr)
    {
        std::cout << i << ") " << ptr->question << " / " << ptr->answer << " / " << ptr->format << std::endl;
        ptr = ptr->next;
        i++;
    }
    std::cout << "---------------------------------------------------------------------------" << std::endl;
};

// リスト構造体をCSVで保存
void QuizManager::saveCSV(std::string filePath) {};
// formatを判定
int QuizManager::determineFormat(std::string format) { return 0; };