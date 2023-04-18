#pragma once
#include "question.hpp"

class Pythagorean_Theorem : public Question {
QUESTION_STANDARD_DECL(Pythagorean_Theorem)
public:
	Pythagorean_Theorem(std::mt19937& gen);
private:
	size_t index;
	std::uniform_int_distribution<size_t> question_chooser{0, 2};
	std::uniform_int_distribution<int> val_chooser{100, 4000};
	float answer;
};
