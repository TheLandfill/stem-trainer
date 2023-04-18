#pragma once
#include "question.hpp"

class Pythagorean_Identities : public Question {
QUESTION_STANDARD_DECL(Pythagorean_Identities)
public:
	Pythagorean_Identities(std::mt19937& gen);
private:
	size_t which_identity;
	std::uniform_int_distribution<size_t> identity_chooser{0, 8};
	std::string answer;
};
