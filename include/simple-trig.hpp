#pragma once
#include "question.hpp"

class Simple_Trig : public Question {
QUESTION_STANDARD_DECL(Simple_Trig)
public:
	Simple_Trig(std::mt19937& gen);
private:
	double answer;
	double tolerance;
	std::uniform_int_distribution<> vals{100, 4000};
	std::uniform_int_distribution<> choices{1, 9};
	std::uniform_int_distribution<> rad_or_deg_dec{0, 1};
};
