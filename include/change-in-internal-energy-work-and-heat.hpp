#pragma once
#include "question.hpp"

class Change_In_Internal_Energy_Work_And_Heat : public Question {
QUESTION_STANDARD_DECL(Change_In_Internal_Energy_Work_And_Heat)
public:
	Change_In_Internal_Energy_Work_And_Heat(std::mt19937& gen);
private:
	double answer;
	std::uniform_int_distribution<int> energy_chooser{-100, 100};
};
