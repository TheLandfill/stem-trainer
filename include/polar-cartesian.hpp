#pragma once
#include "question.hpp"

class Polar_And_Cartesian : public Question {
QUESTION_STANDARD_DECL(Polar_And_Cartesian)
public:
	Polar_And_Cartesian(std::mt19937& gen);
private:
	std::uniform_int_distribution<int> cart_chooser{-100, 100};
	std::uniform_int_distribution<size_t> radius_chooser{5, 100};
	std::uniform_int_distribution<size_t> angle_chooser{0, 720};
	std::uniform_int_distribution<size_t> polar_or_cartesian_answer_chooser{0, 1};
	std::uniform_int_distribution<size_t> first_or_second_coord_chooser{0, 1};
	double answer;
};
