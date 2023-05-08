#pragma once
#include "question.hpp"

class Function_Transformations : public Question {
QUESTION_STANDARD_DECL(Function_Transformations)
public:
	Function_Transformations(std::mt19937& gen);
private:
	enum FUNC_CHOICE {
		LR = 0,
		UD,
		HS,
		VS,
		FL
	};
	std::uniform_int_distribution<size_t> transformation_chooser{0, 4};
	std::uniform_int_distribution<size_t> text_or_function_chooser{0, 1};
	std::uniform_int_distribution<int> number_chooser{-10, 10};
	std::string answer;
};
