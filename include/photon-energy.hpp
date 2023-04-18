#pragma once
#include "question.hpp"

class Photon_Energy : public Question {
QUESTION_STANDARD_DECL(Photon_Energy)
public:
	Photon_Energy(std::mt19937& gen);
private:
	double answer;
	std::uniform_int_distribution<size_t> wavelength_chooser{300, 800};
};
