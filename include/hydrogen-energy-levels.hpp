#pragma once
#include "question.hpp"

class Hydrogen_Energy_Levels : public Question {
QUESTION_STANDARD_DECL(Hydrogen_Energy_Levels)
public:
	Hydrogen_Energy_Levels(std::mt19937& gen);
private:
	double answer;
	std::uniform_int_distribution<size_t> energy_level_chooser{1, 5};
	std::uniform_int_distribution<size_t> answer_chooser{0, 2};
};
