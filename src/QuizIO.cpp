#include "../include/QuizIO.h"
#include "../include/QuizManager.h"
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <filesystem>
#include <chrono>
#include <iomanip>
#include <regex>

QuizIO::QuizIO() {};

QuizIO::~QuizIO() {};

// リスト構造体をCSVから読み込み
bool QuizIO::loadCSV(const std::string &csvPath, QuizManager &quiz)
{
    // 拡張子チェック（小文字で比較）
    std::filesystem::path p(csvPath);
    auto ext = p.extension().string();
    std::transform(ext.begin(), ext.end(), ext.begin(), [](unsigned char c){ return std::tolower(c); });
    if (ext != ".csv"){
        std::cout << "Not a CSV file." << std::endl;
        return false;
    }    
    
    // 開けるか確認
    std::ifstream file(csvPath);
    if (!file.is_open()) {
        std::cout << "Failed to open file: " << csvPath << std::endl;
        return false;
    }

    std::string line;
    // ヘッダー行を読み込み
    if (!std::getline(file, line)) {
        file.close();
        std::cout << "Empty file: " << csvPath << std::endl;
        return false; // 空ファイルは失敗扱い
    }

    // ヘッダー解析
    std::stringstream ss(line);
    std::string header;
    size_t qIdx = 0, aIdx = 0, fIdx = 0, idx = 0;
    while (std::getline(ss, header, ',')) {
        // 改行コードや空白を削除
        size_t end = header.find_last_not_of(" \t\r\n");
        if (end != std::string::npos) {
            header = header.substr(0, end + 1);
        }
        // ヘッダーの位置を特定
        if (header == "Question"){
            qIdx = idx;
        } else if (header == "Answer") {
            aIdx = idx;
        } else if (header == "Format") {
            fIdx = idx;
        } else {
            file.close();
            std::cout << "Invalid header: " << header << std::endl;
            return false; // 不正なヘッダー
        }
         ++idx;   
    }
    
    // データ行を読み込み
    while (std::getline(file, line)) {
        if (line.empty()) continue;
        
        std::stringstream ss(line);
        std::string column;
        idx = 0;
        std::string question, answer, format;
        // 列解析
        while (std::getline(ss, column, ',')) {
            // 改行コードや空白を削除
            size_t end = column.find_last_not_of(" \t\r\n");
            if (end != std::string::npos) {
                header = header.substr(0, end + 1);
            }
            // 各列を対応する変数に格納
            if (idx == qIdx){
                question = column;
            } else if (idx == aIdx) {
                answer = column;
            } else if (idx == fIdx) {
                format = column;
            } else {
                file.close();
                std::cout << "Invalid column index: " << idx << std::endl;
                return false;
            }
            ++idx;   
        }   
        // ノード作成
        quiz.newNode(question, answer, format);
    }

    file.close();
    return true;
};

// リスト構造体をCSVで保存
void QuizIO::saveCSV(const std::string &savePath, QuizManager &quiz)
{    
    // 現在の日付を取得
    auto now = std::chrono::system_clock::now();
    auto time = std::chrono::system_clock::to_time_t(now);
    std::stringstream datetime;
    datetime << std::put_time(std::localtime(&time), "%Y%m%d-%H%M%S");

    // 日時部分を削除
    std::filesystem::path p(savePath);
    std::string fileName = p.stem().string();
    std::regex re(R"(_\d{8}-\d{6})"); // 日時の正規表現
    std::smatch match;
    if (std::regex_search(fileName, match, re)) {
        fileName = match.prefix().str();
    }
    // 保存パスの生成 ({quizName}_{日時}.csv)
    auto saveFilePath = p.parent_path() / (fileName + "_" + datetime.str() + ".csv");

    // ファイルを開く
    std::ofstream file(saveFilePath);

    // データの書き込み
    file << "Question,Answer,Format\n";
    quizzes *ptr = quiz.getHead();
    while (ptr) {        
        file << ptr->question << "," << ptr->answer << "," << ptr->format << "\n";
        ptr = ptr->next;
    }

    file.close();

};