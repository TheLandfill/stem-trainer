#include "radians-to-degrees.hpp"
#include <iostream>
#include <iomanip>
#include <sstream>

Radians_To_Degrees::Radians_To_Degrees(std::mt19937& gen) {
	change_vals(gen);
}

bool Radians_To_Degrees::check_answer(const std::string& user_ans) {
	double user_num_ans;
	try {
		user_num_ans = std::stod(user_ans);
	} catch(std::invalid_argument e) {
		return false;
	}
	return (std::abs(user_num_ans - answer) <= 0.1);
}

void Radians_To_Degrees::change_vals(std::mt19937& gen) {
	std::stringstream strstr;
	answer = val_chooser(gen);
	double given_value = answer;
	size_t rad_or_deg = rad_or_deg_dec(gen);
	switch (rad_or_deg) {
	case 0:
		given_value = answer * M_PI / 180.0;
		explanation = "Multiply by 180° / (π radians).";
		break;
	case 1:
	default:
		answer *= M_PI / 180.0;
		explanation = "Multiply by (π radians) / (180°).";
		break;
	}
	strstr.unsetf(std::ios_base::floatfield);
	const char * angle_units[2]{
		" rad",
		"°"
	};
	const char * other_angle_unit_names[2]{
		"degrees",
		"radians"
	};
	strstr << "| Radians and Degrees |: Convert " << std::setprecision(5) << given_value <<
	angle_units[rad_or_deg] << " to " << other_angle_unit_names[rad_or_deg] << ".";
	question = strstr.str();
	explanation += "\n\tAnswer: ";
	explanation += std::to_string(answer);
}

Question * Radians_To_Degrees::make_copy(std::mt19937& gen) {
	return new Radians_To_Degrees{gen};
}

QUESTION_STANDARD_DEFN(Radians_To_Degrees)
