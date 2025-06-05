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
    void newNode(std::string question, std::string answer, std::string format);
    // 指定したindexのノードを削除
    void deleteNode(int num);
    // リスト構造体を表示
    void display();
    // リスト構造体をCSVで保存
    void saveCSV(std::string filePath);
    // formatを判定
    int determineFormat(std::string format);
};