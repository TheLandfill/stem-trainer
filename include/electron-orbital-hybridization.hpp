#pragma once
#include "question.hpp"

class Electron_Orbital_Hybridization : public Question {
QUESTION_STANDARD_DECL(Electron_Orbital_Hybridization)
public:
	Electron_Orbital_Hybridization(std::mt19937& gen);
private:
	size_t steric_number;
	std::uniform_int_distribution<size_t> steric_number_chooser{1, 6};
};
