#pragma once
#include "question.hpp"

class Unit_Circle : public Question {
QUESTION_STANDARD_DECL(Unit_Circle)
public:
	Unit_Circle(std::mt19937& gen, size_t which_func);
private:
	size_t which_func;
	std::string answer;
	std::uniform_int_distribution<size_t> theta_chooser{0, 15};
	std::uniform_int_distribution<size_t> rad_or_deg_dec{0, 1};
};
