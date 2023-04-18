#pragma once
#include "question.hpp"

class Number_Of_Core_Electrons : public Question {
QUESTION_STANDARD_DECL(Number_Of_Core_Electrons)
public:
	Number_Of_Core_Electrons(std::mt19937& gen);
private:
	size_t answer;
	std::uniform_int_distribution<size_t> element_chooser{1, 83};
};

