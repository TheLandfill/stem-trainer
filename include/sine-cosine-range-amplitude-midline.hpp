#pragma once
#include "question.hpp"

class Sine_Cosine_Range_Amplitude_Midline : public Question {
QUESTION_STANDARD_DECL(Sine_Cosine_Range_Amplitude_Midline)
public:
	Sine_Cosine_Range_Amplitude_Midline(std::mt19937& gen);
private:
	int answer;
	std::uniform_int_distribution<size_t> given_mid_ar_or_range{0, 1};
	std::uniform_int_distribution<size_t> desired_value_chooser{0, 1};
	std::uniform_int_distribution<size_t> sin_or_cos_chooser{0, 1};
	std::uniform_int_distribution<int> range_chooser{-25, 25};
};
