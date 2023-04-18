#include "specific-heat-capacity.hpp"
#include <iostream>
#include <sstream>
#include <iomanip>

Specific_Heat_Capacity::Specific_Heat_Capacity(std::mt19937& gen) {
	change_vals(gen);
}

bool Specific_Heat_Capacity::check_answer(const std::string& user_ans) {
	double user_num_ans;
	try {
		user_num_ans = std::stod(user_ans);
	} catch(std::invalid_argument e) {
		return false;
	}
	return ((std::abs(user_num_ans - answer) / answer) <= 0.005);
}

void Specific_Heat_Capacity::change_vals(std::mt19937& gen) {
	double specific_heat_capacity = specific_heat_capacity_chooser(gen) / 1000.0;
	double delta_T = delta_T_chooser(gen);
	while (std::abs(delta_T) < 50) {
		delta_T = delta_T_chooser(gen);
	}
	delta_T /= 10.0;
	double mass = mass_chooser(gen);
	double delta_E = mass * specific_heat_capacity * delta_T;
	missing_variable = missing_variable_chooser(gen);
	std::stringstream strstr;
	strstr << "| Specific Heat Capacity |:\n";
	switch (missing_variable) {
	case 0:
		strstr << "A substance has a heat capacity of " << specific_heat_capacity << "J/(g °C)\n"
		"and experiences a temperature change of " << delta_T << "°C.\n"
		"If the substance has a mass of " << mass << "g, what is the\n"
		"net flow of heat into the substance?\n"
		"Give your answer in Joules.";
		answer = delta_E;
		break;
	case 1:
		strstr << "A substance has a heat capacity of " << specific_heat_capacity << "J/(g K)\n"
		"and has ";
		if (delta_E < 0) {
			strstr << -delta_E << "J flowing out of the substance.";
		} else {
			strstr << delta_E << "J flowing into the substance.";
		}
		strstr << "\nIf the substance has a mass of " << mass << "g, find the\nchange in temperature of the substance.\n"
		"Give your answer in °C.";
		answer = delta_T;
		break;
	case 2:
		strstr << "A substance has a heat capacity of " << specific_heat_capacity << "J/(g K)\n"
		"and has ";
		if (delta_E < 0) {
			strstr << -delta_E << " J of heat flowing out of the substance.";
		} else {
			strstr << delta_E << " J of heat flowing into the substance.";
		}
		strstr << "\nIf the net change in temperature of the substance is " << delta_T << "°C,\nfind the mass of the substance.\n"
		"Give your answer in grams (g).";
		answer = mass;
		break;
	case 3:
	default:
		strstr << "A substance has has ";
		if (delta_E < 0) {
			strstr << -delta_E << " J of heat flowing out of it.";
		} else {
			strstr << delta_E << " J of heat flowing into it.";
		}
		strstr << "\nIn this process, the temperature of the substance"
		"\nhas a net change of " << delta_T << "°C. If the mass of the\n"
		"substance is " << mass << "g, find the specific heat capacity.\n"
		"Give your answer in J/(g°C).";
		answer = specific_heat_capacity;
		break;
	}
	question = strstr.str();
	explanation =
	"Use the formula q = m C_s ΔT, where\n\t"
	"q = heat flow/change in energy\n\t"
	"m = mass\n\t"
	"C_s = specific heat capacity\n\t"
	"ΔT = change in temperature.";
	explanation += "\n\tAnswer: ";
	explanation += std::to_string(answer);
}

Question * Specific_Heat_Capacity::make_copy(std::mt19937& gen) {
	return new Specific_Heat_Capacity{gen};
}

QUESTION_STANDARD_DEFN(Specific_Heat_Capacity)
