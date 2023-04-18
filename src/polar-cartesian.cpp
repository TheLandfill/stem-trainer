#include "polar-cartesian.hpp"
#include <iostream>
#include <sstream>
#include <iomanip>

Polar_And_Cartesian::Polar_And_Cartesian(std::mt19937& gen) {
	change_vals(gen);
}

bool Polar_And_Cartesian::check_answer(const std::string& user_ans) {
	double user_num_ans;
	try {
		user_num_ans = std::stod(user_ans);
	} catch(std::invalid_argument e) {
		return false;
	}
	return (std::abs(user_num_ans - answer) <= 0.1);
}

void Polar_And_Cartesian::change_vals(std::mt19937& gen) {
	std::stringstream strstr;
	bool cartesian_answer = polar_or_cartesian_answer_chooser(gen);
	if (cartesian_answer) {
		bool x_answer = first_or_second_coord_chooser(gen);
		double r = (double)radius_chooser(gen) / 10.0;
		double theta = (double)angle_chooser(gen);
		strstr << "A point P lies on a circle centered at\nthe origin with a radius " << std::fixed << std::setprecision(1) << r << " and forms\nthe angle " << theta << "° with the x-axis. Find\n";
		theta *= M_PI / 180.0;
		if (x_answer) {
			strstr << "its x coordinate";
			answer = r * cos(theta);
			explanation = "You should have calculated\n\tr * cos(θ).";
		} else {
			strstr << "its y coordinate";
			answer = r * sin(theta);
			explanation = "You should have calculated\n\tr * sin(θ).";
		}
		strstr << " to one digit after the\ndecimal place.";
	} else {
		bool r_answer = first_or_second_coord_chooser(gen);
		double x = (double)cart_chooser(gen);
		double y = (double)cart_chooser(gen);
		while (std::abs(x - y) < 3.0) {
			x = (double)cart_chooser(gen);
		}
		x /= 10.0;
		y /= 10.0;
		strstr << "A point P has coordinates (" << std::fixed << std::setprecision(1) << x << ", " << y << ") and\nlies on a circle centered at the origin.\nFind ";
		if (r_answer) {
			strstr << "the radius of the circle";
			answer = sqrt(x * x + y * y);
			explanation = "You should have calculated\n\tsqrt(x² + y²)";
		} else {
			strstr << "the angle the line through the origin\nand P "
			"makes with the x-axis";
			answer = 180.0 * atan2(y, x) / M_PI;
			explanation = "You should have calculated"
				"\n\tatan(y / x)"
				"\n\tand then figured out which quadrant"
				"\n\tthe angle was in.";
		}
		strstr << " to one digit\nafter the decimal place.";
	}
	question = strstr.str();
	explanation += "\n\tAnswer: ";
	explanation += std::to_string(answer);
}

Question * Polar_And_Cartesian::make_copy(std::mt19937& gen) {
	return new Polar_And_Cartesian{gen};
}

QUESTION_STANDARD_DEFN(Polar_And_Cartesian)
