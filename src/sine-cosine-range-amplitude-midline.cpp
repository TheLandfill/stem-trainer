#include "sine-cosine-range-amplitude-midline.hpp"
#include <iostream>

Sine_Cosine_Range_Amplitude_Midline::Sine_Cosine_Range_Amplitude_Midline(std::mt19937& gen) {
	change_vals(gen);
}

bool Sine_Cosine_Range_Amplitude_Midline::check_answer(const std::string& user_ans) {
	double user_num_ans;
	try {
		user_num_ans = std::stod(user_ans);
	} catch(std::invalid_argument e) {
		return false;
	}
	return (std::abs(user_num_ans - answer) <= 0.1);
}

void Sine_Cosine_Range_Amplitude_Midline::change_vals(
	std::mt19937& gen
) {
	int v1 = range_chooser(gen);
	int v2 = range_chooser(gen);
	while (v2 == v1) {
		v2 = range_chooser(gen);
	}
	int min = std::min(v1, v2);
	int max = std::max(v1, v2);
	max += ((max - min) % 2);
	int amp = max - min;
	amp /= 2;
	int midval = min + amp;
	size_t sin_or_cos = sin_or_cos_chooser(gen);
	const char * sin_or_cos_text[2]{
		"sine",
		"cosine"
	};
	size_t mid_ar_or_range = given_mid_ar_or_range(gen);
	question = "| Sine or Cosine Amplitude, Range, and Midline |\n";
	if (mid_ar_or_range == 0) {
		size_t want_max_or_min = desired_value_chooser(gen);
		question += "Given that a ";
		question += sin_or_cos_text[sin_or_cos];
		question += " function has a midline of y = ";
		question += std::to_string(midval);
		question += "\nand an amplitude of ";
		question += std::to_string(amp);
		question += ", find its ";
		switch (want_max_or_min) {
		case 0:
			answer = min;
			question += "minimum value.";
			explanation = "You should have calculated\n\t(midline) - (amplitude)";
			break;
		case 1:
			answer = max;
			question += "maximum value.";
			explanation = "You should have calculated\n\t(midline) + (amplitude)";
			break;
		}
	} else if (mid_ar_or_range == 1) {
		question += "Given that a ";
		question += sin_or_cos_text[sin_or_cos];
		question += " function has a minimum of ";
		question += std::to_string(min);
		question += "\nand a maximum of ";
		question += std::to_string(max);
		question += ", find its ";
		size_t want_mid_or_amp = desired_value_chooser(gen);
		switch (want_mid_or_amp) {
		case 0:
			answer = midval;
			question += "midline.";
			explanation = "You should have calculated\n\t((max) + (min)) / 2";
			break;
		case 1:
			answer = amp;
			question += "amplitude.";
			explanation = "You should have calculated\n\t((max) - (min)) / 2";
			break;
		}
	}
	explanation += "\n\tAnswer: ";
	explanation += std::to_string(answer);
}

Question * Sine_Cosine_Range_Amplitude_Midline::make_copy(std::mt19937& gen) {
	return new Sine_Cosine_Range_Amplitude_Midline{gen};
}

QUESTION_STANDARD_DEFN(Sine_Cosine_Range_Amplitude_Midline)
