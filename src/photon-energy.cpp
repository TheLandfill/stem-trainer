#include "photon-energy.hpp"
#include <iostream>
#include <sstream>
#include <iomanip>

Photon_Energy::Photon_Energy(std::mt19937& gen) {
	change_vals(gen);
}

bool Photon_Energy::check_answer(const std::string& user_ans) {
	double user_num_ans;
	try {
		user_num_ans = std::stod(user_ans);
	} catch(std::invalid_argument e) {
		std::cerr << "That is not a valid number.\n";
		return false;
	}
	return (
		(std::abs(user_num_ans - answer) / answer) <= 0.01
	);
}

void Photon_Energy::change_vals(std::mt19937& gen) {
	std::stringstream strstr;
	double wavelength = wavelength_chooser(gen);
	double frequency = 3.0e8 * 1.0e9 / wavelength;
	strstr << "What is the energy of a photon with a wavelength of " << wavelength << " nm?\nGive your answer in Joules.";
	strstr << "\nTo write 7.5 × 10⁸ or 7.5 * 10^8, use the notation 7.5e8.";
	double h = 6.626e-34;
	answer = h * frequency;
	question = strstr.str();
	strstr.str(std::string{});
	strstr.clear();
	strstr << "Use the formula (speed of light) = (wavelength) × (frequency) to get the frequency,\n\tthen multiply by Planck's Constant (approx 6.626 * 10^-34 J s)\n\t"
	"Note that you have to convert the speed of light into nm / s to use\n\t"
	"the formula with standard values for light and frequency.\n\tAnswer: ";
	strstr << std::scientific << std::setprecision(3) << answer;
	explanation = strstr.str();
}

Question * Photon_Energy::make_copy(std::mt19937& gen) {
	return new Photon_Energy{gen};
}

QUESTION_STANDARD_DEFN(Photon_Energy)
