#include "number-of-photons.hpp"
#include <iostream>
#include <sstream>
#include <iomanip>

Number_Of_Photons::Number_Of_Photons(std::mt19937& gen) {
	change_vals(gen);
}

bool Number_Of_Photons::check_answer(const std::string& user_ans) {
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

void Number_Of_Photons::change_vals(std::mt19937& gen) {
	std::stringstream strstr;
	strstr << "| Number Of Photons |\n";
	double wavelength = wavelength_chooser(gen);
	double frequency = 3.0e8 * 1.0e9 / wavelength;
	double energy = energy_chooser(gen);
	strstr <<
	"How many photons are there in a flash of light (or\n"
	"electromagnetic radiation) with a wavelength of\n"
	<< wavelength << " nm that releases " << energy << " kJ?";
	strstr << "\nTo write 7.5 × 10⁸ or 7.5 * 10^8, use the notation 7.5e8.";
	double h = 6.626e-34;
	double photon_energy = h * frequency;
	answer = energy * 1e3 / photon_energy;
	question = strstr.str();
	strstr.str(std::string{});
	strstr.clear();
	strstr << "Divide the total energy of the flash by the energy of a\n\t"
	"single photon, which you can calculate using E_photon = hc/λ\n\t"
	"Answer: ";
	strstr << std::scientific << std::setprecision(3) << answer;
	explanation = strstr.str();
}

Question * Number_Of_Photons::make_copy(std::mt19937& gen) {
	return new Number_Of_Photons{gen};
}

QUESTION_STANDARD_DEFN(Number_Of_Photons)
