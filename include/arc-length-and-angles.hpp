#pragma once
#include "question.hpp"

class Arc_Length_And_Angles : public Question {
QUESTION_STANDARD_DECL(Arc_Length_And_Angles)
public:
	Arc_Length_And_Angles(std::mt19937& gen);
private:
	size_t missing_variable;
	std::uniform_int_distribution<size_t> length_chooser{10, 40};
	std::uniform_int_distribution<size_t> angle_chooser{10, 360};
	std::uniform_int_distribution<size_t> missing_variable_chooser{0, 2};
	double answer;
};
