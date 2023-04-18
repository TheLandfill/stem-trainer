#include "wavelength-and-frequency.hpp"
#include <iostream>
#include <sstream>
#include <iomanip>

Wavelength_And_Frequency::Wavelength_And_Frequency(std::mt19937& gen) {
	change_vals(gen);
}

bool Wavelength_And_Frequency::check_answer(const std::string& user_ans) {
	double user_num_ans;
	try {
		user_num_ans = std::stod(user_ans);
	} catch(std::invalid_argument e) {
		return false;
	}
	return (
		(std::abs(user_num_ans - answer) / answer) <= 0.01
	);
}

void Wavelength_And_Frequency::change_vals(std::mt19937& gen) {
	std::stringstream strstr;
	strstr << "| Wavelength And Frequency |\n";
	double wavelength = wavelength_chooser(gen);
	double frequency = 3.0e8 * 1.0e9 / wavelength;
	bool answer_is_wavelength = wl_or_freq_chooser(gen);
	if (answer_is_wavelength) {
		answer = wavelength;
		strstr << "What is the wavelength of light with a frequency of " << std::scientific << std::setprecision(5) << frequency << " s^-1?";
		strstr << "\nGive your answer in nm to one digit after the decimal.";
	} else {
		answer = frequency;
		strstr << "What is the frequency of light with a wavelength of " << std::fixed << std::setprecision(1) << wavelength << " nm ?";
		strstr << "\nGive your answer in s^-1 to three digits after the decimal.";
	}
	strstr << "\nTo write 7.5 × 10⁸ or 7.5 * 10^8, use the notation 7.5e8.";
	question = strstr.str();
	strstr.str(std::string{});
	strstr.clear();
	strstr << "Use the formula (speed of light) = (wavelength) × (frequency)\n\t"
	"Note that you have to convert the speed of light into nm / s to use\n\t"
	"the formula with standard values for light and frequency.\n\tAnswer: ";
	if (answer_is_wavelength) {
		strstr << std::fixed << std::setprecision(1) << answer;
	} else {
		strstr << std::scientific << std::setprecision(5) << answer;
	}
	explanation = strstr.str();
}

Question * Wavelength_And_Frequency::make_copy(std::mt19937& gen) {
	return new Wavelength_And_Frequency{gen};
}

QUESTION_STANDARD_DEFN(Wavelength_And_Frequency)
