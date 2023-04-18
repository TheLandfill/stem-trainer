#pragma once
#include "question.hpp"

class Radians_To_Degrees : public Question {
QUESTION_STANDARD_DECL(Radians_To_Degrees)
public:
	Radians_To_Degrees(std::mt19937& gen);
private:
	size_t rad_or_deg;
	std::uniform_int_distribution<size_t> rad_or_deg_dec{0, 1};
	std::uniform_int_distribution<size_t> val_chooser{0, 360};
	double answer;
};
