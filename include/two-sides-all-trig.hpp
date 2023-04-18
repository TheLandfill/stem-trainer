#pragma once
#include "question.hpp"

class Two_Sides_All_Trig : public Question {
QUESTION_STANDARD_DECL(Two_Sides_All_Trig)
public:
	Two_Sides_All_Trig(std::mt19937& gen);
private:
	double answer;
	std::uniform_int_distribution<size_t> length_chooser{100, 400};
	std::uniform_int_distribution<size_t> side_chooser{0, 2};
	std::uniform_int_distribution<size_t> func_chooser{0, 5};
};
