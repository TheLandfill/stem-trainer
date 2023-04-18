#pragma once
#include "question.hpp"

class Number_Of_Photons : public Question {
QUESTION_STANDARD_DECL(Number_Of_Photons)
public:
	Number_Of_Photons(std::mt19937& gen);
private:
	double answer;
	std::uniform_int_distribution<size_t> wavelength_chooser{300, 800};
	std::uniform_int_distribution<size_t> energy_chooser{10, 900};
};
