#pragma once
#include "question.hpp"

class Extract_Info_From_Trig_Function : public Question {
QUESTION_STANDARD_DECL(Extract_Info_From_Trig_Function)
public:
	Extract_Info_From_Trig_Function(std::mt19937& gen);
private:
	std::string answer;
	// Period, Amplitude, Min, Max, Average, Midline
	std::uniform_int_distribution<size_t> answer_chooser{0, 5};
	std::uniform_int_distribution<size_t> sin_or_cos_chooser{0, 1};
	std::uniform_int_distribution<int> val_chooser{-20, 20};
	std::uniform_int_distribution<int> period_chooser{1, 20};
	std::uniform_int_distribution<size_t> rational_or_irrational_period_chooser{0, 1};
};
