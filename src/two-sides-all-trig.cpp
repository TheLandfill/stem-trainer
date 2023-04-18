#include "two-sides-all-trig.hpp"
#include <iostream>
#include <sstream>
#include <iomanip>

Two_Sides_All_Trig::Two_Sides_All_Trig(std::mt19937& gen) {
	change_vals(gen);
}

bool Two_Sides_All_Trig::check_answer(const std::string& user_ans) {
	double user_num_ans;
	try {
		user_num_ans = std::stod(user_ans);
	} catch(std::invalid_argument e) {
		return false;
	}
	return (std::abs(user_num_ans - answer) <= 0.1);
}

void Two_Sides_All_Trig::change_vals(std::mt19937& gen) {
	size_t side_to_leave_out = side_chooser(gen);
	size_t func_chosen = func_chooser(gen);
	double x = length_chooser(gen) / 10.0;
	double y = length_chooser(gen) / 10.0;
	double h = sqrt(x * x + y * y);
	std::stringstream strstr;
	strstr << "| Trig Function Definitions |: " <<
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
	strstr << std::fixed;
	switch (side_to_leave_out) {
	case 0:
		strstr <<
			"x = " <<
			std::setprecision(2) <<
			x <<
			"\ny = " <<
			y;
		break;
	case 1:
		strstr <<
			"x = " <<
			std::setprecision(2) <<
			x <<
			"\nh = " <<
			h;
		break;
	case 2:
	default:
		strstr <<
			"y = " <<
			std::setprecision(2) <<
			y <<
			"\nh = " <<
			h;
		break;
	}
	const char * func_names[6]{
		"sin",
		"cos",
		"tan",
		"csc",
		"sec",
		"cot"
	};
	strstr << "\nFind " << func_names[func_chosen] << "(θ) to three places after the decimal.";
	question = strstr.str();
	explanation = "You should have calculated\n\t";
	switch (func_chosen) {
	case 0:
		answer = y / h;
		explanation += "y / h";
		break;
	case 1:
		answer = x / h;
		explanation += "x / h";
		break;
	case 2:
		answer = y / x;
		explanation += "y / x";
		break;
	case 3:
		answer = h / y;
		explanation += "h / y";
		break;
	case 4:
		answer = h / x;
		explanation += "h / x";
		break;
	case 5:
		answer = x / y;
		explanation += "x / y";
		break;
	}
	explanation += "\n\tAnswer: ";
	explanation += std::to_string(answer);
}

Question* Two_Sides_All_Trig::make_copy(std::mt19937& gen) {
	return new Two_Sides_All_Trig{gen};
}

QUESTION_STANDARD_DEFN(Two_Sides_All_Trig)
