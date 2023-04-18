#include "simple-trig.hpp"
#include <cmath>
#include <iostream>
#include <sstream>
#include <iomanip>

Simple_Trig::Simple_Trig(std::mt19937& gen) {
	change_vals(gen);
}

bool Simple_Trig::check_answer(const std::string& user_ans) {
	double user_num_ans;
	try {
		user_num_ans = std::stod(user_ans);
	} catch(std::invalid_argument e) {
		std::cerr << "That is not a valid number.\n";
		return false;
	}
	return (std::abs(user_num_ans - answer) <= tolerance);
}

void Simple_Trig::change_vals(std::mt19937& gen) {
	std::stringstream strstr;
	strstr << "| Standard Trig |: " <<
R"""(Given the following right triangle
               .
              /|
             / |
            /  |
         h /   | y
          /    |
         /     |
        /\θ    |
       /-------+
           x
and
)""";
	int x_int = vals(gen);
	int y_int = vals(gen);
	double x = x_int;
	x /= 10.0;
	double y = y_int;
	y /= 10.0;
	double h = sqrt(x * x + y * y);
	double theta = atan2(y, x);
	unsigned int choice = choices(gen);
	unsigned int rad_or_deg = rad_or_deg_dec(gen);
	std::string in_rad_deg_strs[]{
		"degrees to three digits after the decimal.",
		"radians to three digits after the decimal.",
	};
	double theta_mult[]{
		180.0 / M_PI,
		1.0
	};
	std::string theta_units[]{
		"°",
		" rad"
	};
	int num_theta_digits[]{
		3,
		6
	};
	tolerance = 0.01;
	strstr << std::fixed;
	switch (choice) {
	// Given x and theta, solve for y
	case 1:
		strstr <<
			"x = " <<
			std::setprecision(2) <<
			x <<
			"\nθ = " <<
			std::setprecision(num_theta_digits[rad_or_deg]) <<
			theta * theta_mult[rad_or_deg] <<
			theta_units[rad_or_deg] <<
			"\nSolve for y to one digit after the decimal.";
		answer = x * tan(theta);
		explanation = "You should have calculated\n\ty = x * tan(θ).";
		tolerance = 0.1;
		break;
	// Given x and theta, solve for h
	case 2:
		strstr <<
			"x = " <<
			std::setprecision(2) <<
			x <<
			"\nθ = " <<
			std::setprecision(num_theta_digits[rad_or_deg]) <<
			theta * theta_mult[rad_or_deg] <<
			theta_units[rad_or_deg] <<
			std::setprecision(num_theta_digits[rad_or_deg]) <<
			"\nSolve for h to one digit after the decimal.";
		answer = x / cos(theta);
		explanation = "You should have calculated\n\th = x / cos(θ).";
		tolerance = 0.1;
		break;
	// Given y and theta, solve for x
	case 3:
		strstr <<
			"y = " <<
			std::setprecision(2) <<
			y <<
			"\nθ = " <<
			std::setprecision(num_theta_digits[rad_or_deg]) <<
			theta * theta_mult[rad_or_deg] <<
			theta_units[rad_or_deg] <<
			"\nSolve for x to one digit after the decimal.";
		answer = y / tan(theta);
		explanation = "You should have calculated\n\tx = y / tan(θ).";
		tolerance = 0.1;
		break;
	// Given y and theta, solve for h
	case 4:
		strstr <<
			"y = " <<
			std::setprecision(2) <<
			y <<
			"\nθ = " <<
			std::setprecision(num_theta_digits[rad_or_deg]) <<
			theta * theta_mult[rad_or_deg] <<
			theta_units[rad_or_deg] <<
			"\nSolve for h to one digit after the decimal.";
		answer = y / sin(theta);
		explanation = "You should have calculated\n\th = y / sin(θ).";
		tolerance = 0.1;
		break;
	// Given h and theta, solve for x
	case 5:
		strstr <<
			"h = " <<
			std::setprecision(2) <<
			h <<
			"\nθ = " <<
			std::setprecision(num_theta_digits[rad_or_deg]) <<
			theta * theta_mult[rad_or_deg] <<
			theta_units[rad_or_deg] <<
			"\nSolve for x to one digit after the decimal.";
		answer = h * cos(theta);
		explanation = "You should have calculated\n\tx = h * cos(θ).";
		tolerance = 0.1;
		break;
	// Given h and theta, solve for y
	case 6:
		strstr <<
			"h = " <<
			std::setprecision(2) <<
			h <<
			"\nθ = " <<
			std::setprecision(num_theta_digits[rad_or_deg]) <<
			theta * theta_mult[rad_or_deg] <<
			theta_units[rad_or_deg] <<
			"\nSolve for y to one digit after the decimal.";
		answer = h * sin(theta);
		explanation = "You should have calculated\n\ty = h * sin(θ).";
		tolerance = 0.1;
		break;
	// Given x and y, solve for theta
	case 7:
		strstr <<
			"x = " <<
			std::setprecision(2) <<
			x <<
			"\ny = " <<
			y <<
			"\nSolve for theta in " <<
			in_rad_deg_strs[rad_or_deg];
		answer = atan2(y, x) * theta_mult[rad_or_deg];
		explanation = "You should have calculated\n\tθ = atan(y / x).";
		break;
	// Given x and h, solve for theta
	case 8:
		strstr <<
			"x = " <<
			std::setprecision(2) <<
			x <<
			"\nh = " <<
			h <<
			"\nSolve for theta in " <<
			in_rad_deg_strs[rad_or_deg];
		answer = acos(x / h) * theta_mult[rad_or_deg];
		explanation = "You should have calculated\n\tθ = acos(x / h).";
		break;
	// Given y and h, solve for theta
	case 9:
	default:
		strstr <<
			"y = " <<
			std::setprecision(2) <<
			y <<
			"\nh = " <<
			h <<
			"\nSolve for theta in " <<
			in_rad_deg_strs[rad_or_deg];
		answer = asin(y / h) * theta_mult[rad_or_deg];
		explanation = "You should have calculated\n\tθ = asin(y / h).";
		break;
	}
	question = strstr.str();
	explanation += "\n\tAnswer: ";
	explanation += std::to_string(answer);
}

Question* Simple_Trig::make_copy(std::mt19937& gen) {
	return new Simple_Trig{gen};
}

QUESTION_STANDARD_DEFN(Simple_Trig)
