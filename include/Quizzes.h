#pragma once

#include <string>

struct quizzes
{
    std::string question;
    std::string answer;
    std::string format;
    quizzes *next;
};