#include "../include/QuizManager.h"
#include <string>
#include <iostream>

QuizManager::QuizManager()
{
    root->next = nullptr;
};

QuizManager::~QuizManager() {};

// 末尾に新規ノードを作成
void QuizManager::newNode(const std::string &question, const std::string &answer, const std::string &format)
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
void QuizManager::deleteNode(quizzes *target)
{
    if (!target || !root) return;

    quizzes *ptr = root;
    // targetの前のノードを探す
    while (ptr->next && ptr->next != target) {
        ptr = ptr->next;
    }

    // targetが見つかった場合
    if (ptr->next == target) {
        ptr->next = target->next;
        delete target;
    }
}

// リスト構造体を表示
void QuizManager::display()
{
    quizzes *ptr = root->next;
    int i = 1;

    // system("clear"); // コンソールをクリア
    std::cout <<  std::endl;
    std::cout << "---------------------------------------------------------------------------" << std::endl;
    while (ptr)
    {
        std::cout << i << ") " << ptr->question << " / " << ptr->answer << " / " << ptr->format << std::endl;
        ptr = ptr->next;
        ++i;
    }
    std::cout << "---------------------------------------------------------------------------" << std::endl;
};

// quizzes から出題を行う（標準入出力を使用）
bool QuizManager::startQuiz()
{
    // 問題数を入力
    std::string input;
    int quizzesNum;
    std::cout << "How many quizzes will you solve? >> ";
    std::getline(std::cin, input);
    quizzesNum = std::stoi(input);

    int correct = 0;
    std::string userInput;
    quizzes *ptr = root->next;
    system("clear"); // コンソールをクリア

    // 問題数分ループ
    for (int i = 1; i <= quizzesNum; ++i) {
        // 問題がもうない場合
        if (!ptr) {
            std::cout << "Congratulations!" << std::endl;
            return false;
        }
        // 問題の表示と回答の入力
        std::cout << "--------------------------------------------------" << std::endl;
        std::cout << "問題 " << i << ": " << ptr->question << std::endl;
        std::cout << "回答: ";
        if (!std::getline(std::cin, userInput)) {
            std::cout << "Input could not be read. Start over." << std::endl;
            return true;
        }

        // 回答の判定
        if (ptr->answer == userInput) {
            std::cout << "Correct!" << std::endl;
            ++correct;
            quizzes *temp = ptr;
            ptr = ptr->next;
            this->deleteNode(temp); // 正解した問題をリストから削除
        } else {
            std::cout << "Wrong. correct: " << ptr->answer << std::endl;
            this->newNode(ptr->question, ptr->answer, ptr->format); // 間違えた問題をリストの末尾に追加
            ptr = ptr->next; // ポインタを次の問題に進める
        }
    }
    // 結果表示
    std::cout << "==================================================" << std::endl;
    std::cout << "Finished. Score: " << correct << " / " << quizzesNum << std::endl;
    std::cout << "==================================================" << std::endl;
    
    // 続行するか確認
    std::cout << "Shall we continue?" << std::endl;
    std::cout << "yes / no >> ";
    std::getline(std::cin, input);
    if (input == "yes" || input == "y") {
        return true; // 続行
    } else if (input == "no" || input == "n"){
        return false; // 終了
    } else {
        std::cout << "Invalid input. Exiting." << std::endl;
        return false; // 不正な入力で終了
    }
}

// 先頭ノードを取得
quizzes* QuizManager::getHead()
{
    return root->next;
};