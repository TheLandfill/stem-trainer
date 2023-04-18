#pragma once
#include "question.hpp"

class Wavelength_And_Frequency : public Question {
QUESTION_STANDARD_DECL(Wavelength_And_Frequency)
public:
	Wavelength_And_Frequency(std::mt19937& gen);
private:
	double answer;
	std::uniform_int_distribution<size_t> wavelength_chooser{300, 800};
	std::uniform_int_distribution<size_t> wl_or_freq_chooser{0, 1};
};
