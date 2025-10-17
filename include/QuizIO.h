#pragma once

#include <string>

class QuizManager;

class QuizIO
{
public:
    QuizIO();
    ~QuizIO();

    // リスト構造体をCSVから読み込み
    bool loadCSV(const std::string &csvPath, QuizManager &quiz);
    // リスト構造体をCSVで保存
    void saveCSV(const std::string &savePath, QuizManager &quiz);
};