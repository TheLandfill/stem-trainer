#include "hydrogen-energy-levels.hpp"
#include <iostream>
#include <sstream>
#include <iomanip>

Hydrogen_Energy_Levels::Hydrogen_Energy_Levels(std::mt19937& gen) {
	change_vals(gen);
}

bool Hydrogen_Energy_Levels::check_answer(const std::string& user_ans) {
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

void Hydrogen_Energy_Levels::change_vals(std::mt19937& gen) {
	std::stringstream strstr;
	strstr << "| Hydrogen Energy Levels |\n";
	size_t n1 = energy_level_chooser(gen);
	size_t n2 = energy_level_chooser(gen);
	while (n2 == n1) {
		n2 = energy_level_chooser(gen);
	}
	double n_initial = std::max(n1, n2);
	double n_final = std::min(n1, n2);
	double rh = 2.18e-18;
	double energy = -rh * (1.0 / n_initial / n_initial - 1.0 / n_final / n_final);
	double h = 6.626e-34;
	double frequency = energy / h;
	double wavelength = 3.0e8 * 1.0e9 / frequency;
	size_t which_value_is_answer = answer_chooser(gen);
	switch (which_value_is_answer) {
	case 0:
		strstr <<
		"What is the energy of a photon emitted when an electron\n"
		"jumps from n = " << (size_t)n_initial << " to n = " << (size_t)n_final << "? Give your answer\nin Joules.";
		explanation =
		"Use the formula R_H (1 / nf^2 - 1 / ni^2) to find the\n\t"
		"energy of the photon. Note that the negative of this value\n\t"
		"is also how much energy the electron lost.";
		answer = energy;
		break;
	case 1:
		strstr <<
		"Determine the final value of n in a hydrogen atom transition\n"
		"if the electron starts in n = " << (size_t)n_initial << " and the atom emits a\n"
		"photon of light with a wavelength of " << std::fixed << std::setprecision(1) << (size_t)wavelength << " nm.";
		explanation =
		"Solve the equation E_transition = R_H (1 / nf^2 - 1 / ni^2) for nf.\n\t"
		"Then use the formula E_photon = hc/λ to find E_photon = E_transition.";
		answer = n_final;
		break;
	case 2:
	default:
		strstr <<
		"Determine the wavelength of the photon emitted in a hydrogen\n"
		"atom transition if the electron starts in n = " << (size_t)n_initial << " and ends with n = " << (size_t)n_final << ".\nGive your answer in nm.";
		explanation =
		"Plug nf and ni into E_transition = R_H (1 / nf^2 - 1 / ni^2)\n\t"
		"to get the energy of the photon. From there, use E_photon = hc/λ.";
		answer = wavelength;
	}
	strstr << "\nTo write 7.5 × 10⁸ or 7.5 * 10^8, use the notation 7.5e8.";
	question = strstr.str();
	strstr.str(std::string{});
	strstr.clear();
	explanation += "\n\tAnswer: ";
	strstr << std::scientific << std::setprecision(3) << answer;
	explanation += strstr.str();
}

Question * Hydrogen_Energy_Levels::make_copy(std::mt19937& gen) {
	return new Hydrogen_Energy_Levels{gen};
}

QUESTION_STANDARD_DEFN(Hydrogen_Energy_Levels)
