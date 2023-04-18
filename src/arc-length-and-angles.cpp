#include "arc-length-and-angles.hpp"
#include <iostream>
#include <sstream>
#include <iomanip>

Arc_Length_And_Angles::Arc_Length_And_Angles(std::mt19937& gen) {
	change_vals(gen);
}

bool Arc_Length_And_Angles::check_answer(const std::string& user_ans) {
	double user_num_ans;
	try {
		user_num_ans = std::stod(user_ans);
	} catch(std::invalid_argument e) {
		std::cerr << "That is not a valid number.\n";
		return false;
	}
	return (std::abs(user_num_ans - answer) <= 0.1);
}

void Arc_Length_And_Angles::change_vals(std::mt19937& gen) {
	double radius = length_chooser(gen) / 10.0;
	double angle = angle_chooser(gen);
	double arc_length = radius * angle * M_PI / 180.0;
	missing_variable = missing_variable_chooser(gen);
	std::stringstream strstr;
	strstr << "| Arc Length and Angles |: ";
	switch (missing_variable) {
	case 0:
		strstr << "Find the radius of an arc with\n" << "arc length = " << arc_length << "\nangle = " << angle << "°\n";
		strstr << "Express your answer to one digit after the decimal.";
		explanation = "You should have converted the angle to radians then calculated\n\t(arc length) / (angle in radians)";
		answer = radius;
		break;
	case 1:
		strstr << "Find the angle of an arc with\n" << "radius = " << radius << "\narc length = " << arc_length << "\n";
		strstr << "Express your answer in degrees.";
		explanation = "You should have calculated\n\t(arc length)/(radius)\n\tthen converted to radians.";
		answer = angle;
		break;
	case 2:
	default:
		strstr << "Find the arc length of an arc with\n" << "radius = " << radius << "\nangle = " << angle << "°\n";
		strstr << "Express your answer to one digit after the decimal.";
		explanation = "You should have converted the angle to radians then calculated\n\t(radius) * (angle in radians)";
		answer = arc_length;
		break;
	}
	question = strstr.str();
	explanation += "\n\tAnswer: ";
	explanation += std::to_string(answer);
}

Question * Arc_Length_And_Angles::make_copy(std::mt19937& gen) {
	return new Arc_Length_And_Angles{gen};
}

QUESTION_STANDARD_DEFN(Arc_Length_And_Angles)
