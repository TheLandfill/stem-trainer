#include "pythagorean-theorem.hpp"
#include <cmath>
#include <iostream>
#include <sstream>
#include <iomanip>

Pythagorean_Theorem::Pythagorean_Theorem(std::mt19937& gen) {
	change_vals(gen);
}

bool Pythagorean_Theorem::check_answer(const std::string& user_ans) {
	double user_num_ans;
	try {
		user_num_ans = std::stod(user_ans);
	} catch(std::invalid_argument e) {
		return false;
	}
	return (std::abs(user_num_ans - answer) <= 0.1);
}

void Pythagorean_Theorem::change_vals(std::mt19937& gen) {
	std::stringstream strstr;
	strstr << "| Pythagorean_Theorem |: " <<
R"""(Given the following right triangle
               .
              /|
             / |
            /  |
         h /   | y
          /    |
         /     |
        /     +|
       /------++
           x
and
)""";
	int x_int = val_chooser(gen);
	int y_int = val_chooser(gen);
	double x = x_int;
	x /= 10.0;
	double y = y_int;
	y /= 10.0;
	double h = sqrt(x * x + y * y);
	size_t choice = question_chooser(gen);
	strstr << std::fixed << std::setprecision(2);
	switch (choice) {
	case 0:
		strstr <<
			"x = " <<
			x <<
			"\ny = " <<
			y <<
			"\nFind h to one digit after the decimal.";
			answer = sqrt(x * x + y * y);
			explanation = "You should have calculated\n\th = sqrt(x^2 + y^2).";
			break;
	case 1:
		strstr <<
			"x = " <<
			x <<
			"\nh = " <<
			h <<
			"\nFind y to one digit after the decimal.";
			answer = sqrt(h * h - x * x);
			explanation = "You should have calculated\n\ty = sqrt(h^2 - x^2).";
			break;
	case 2:
	default:
		strstr <<
			"y = " <<
			y <<
			"\nh = " <<
			h <<
			"\nFind x to one digit after the decimal.";
			answer = sqrt(h * h - y * y);
			explanation = "You should have calculated\n\tx = sqrt(h^2 - y^2).";
			break;
	}
	question = strstr.str();
	explanation += "\n\tAnswer: ";
	explanation += std::to_string(answer);
}

Question* Pythagorean_Theorem::make_copy(std::mt19937& gen) {
	return new Pythagorean_Theorem{gen};
}

QUESTION_STANDARD_DEFN(Pythagorean_Theorem)
