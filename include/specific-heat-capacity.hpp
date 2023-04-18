#pragma once
#include "question.hpp"

class Specific_Heat_Capacity : public Question {
QUESTION_STANDARD_DECL(Specific_Heat_Capacity)
public:
	Specific_Heat_Capacity(std::mt19937& gen);
private:
	size_t missing_variable;
	std::uniform_int_distribution<size_t> specific_heat_capacity_chooser{300, 5000};
	std::uniform_int_distribution<int> delta_T_chooser{-1000, 1000};
	std::uniform_int_distribution<size_t> mass_chooser{100, 4000};
	std::uniform_int_distribution<size_t> missing_variable_chooser{0, 3};
	double answer;
};
