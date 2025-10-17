#pragma once

#include "Quizzes.h"
#include <string>

class QuizManager
{
private:
    /*　
    リスト構造体の先頭
    値を持たない
    */
    quizzes *root = new quizzes();

public:
    QuizManager();
    ~QuizManager();

    // 末尾に新規ノードを作成
    void newNode(const std::string &question, const std::string &answer, const std::string &format);
    // 指定したindexのノードを削除
    void deleteNode(int num);
    // リスト構造体を表示
    void display();
    // 先頭ノードを取得
    quizzes* getHead();
    // formatを判定
    int determineFormat(const std::string &format);
};