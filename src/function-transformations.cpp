#include "function-transformations.hpp"
#include <iostream>
#include <sstream>
#include <iomanip>
#include <algorithm>
#include <cctype>

Function_Transformations::Function_Transformations(std::mt19937& gen) {
	change_vals(gen);
}

bool Function_Transformations::check_answer(const std::string& user_ans) {
	std::string user_ans_copy = user_ans;
	user_ans_copy.erase(std::remove_if(user_ans_copy.begin(), user_ans_copy.end(), isspace), user_ans_copy.end());
	std::string answer_copy = answer;
	answer_copy.erase(std::remove_if(answer_copy.begin(), answer_copy.end(), isspace), answer_copy.end());
	return user_ans_copy.compare(answer_copy) == 0;
}

void Function_Transformations::change_vals(std::mt19937& gen) {
	std::stringstream strstr;
	strstr << "| Function Transformation |\n";
	int number = number_chooser(gen);
	size_t transformation_choice = transformation_chooser(gen);
	if (transformation_choice == LR || transformation_choice == UD) {
		while (number == 0) {
			number = number_chooser(gen);
		}
	} else {
		while (std::abs(number) < 2) {
			number = number_chooser(gen);
		}
	}
	size_t text_answer = text_or_function_chooser(gen);
	switch (text_answer) {
	case 0:
		strstr << "A function f(x) is related to g(x) by\nf(x) = ";
		switch (transformation_choice) {
		case LR:
			strstr << "g(x ";
			answer = "shift ";
			if (number < 0) {
				strstr << "- " << std::abs(number);
				answer += "right ";
			} else {
				strstr << "+ " << number;
				answer += "left ";
			}
			strstr << ")\n";
			answer += std::to_string(std::abs(number));
			answer += " unit";
			break;
		case UD:
			strstr << "g(x) ";
			answer = "shift ";
			if (number < 0) {
				strstr << "- " << std::abs(number);
				answer += "down ";
			} else {
				strstr << "+ " << number;
				answer += "up ";
			}
			strstr << "\n";
			answer += std::to_string(std::abs(number));
			answer += " unit";
			break;
		case HS:
			strstr << "g(";
			answer = "horizontal ";
			if (number < 0) {
				strstr << "x/" << std::abs(number);
				answer += "stretch";
			} else {
				strstr << number << "x";
				answer += "compression";
			}
			strstr << ")\n";
			answer += " by a factor of ";
			if (number > 0) {
				answer += "1/";
			}
			answer += std::to_string(std::abs(number));
			break;
		case VS:
			answer = "vertical ";
			if (number < 0) {
				strstr << "(1/" << std::abs(number) << ")";
				answer += "compression";
			} else {
				strstr << number;
				answer += "stretch";
			}
			strstr << " g(x)\n";
			answer += " by a factor of ";
			if (number < 0) {
				answer += "1/";
			}
			answer += std::to_string(std::abs(number));
			break;
		case FL:
		default:
			answer = "flip over the ";
			if (number < 0) {
				strstr << "-g(x)\n";
				answer += "x-axis";
			} else {
				strstr << "g(-x)\n";
				answer += "y-axis";
			}
			break;
		}
		strstr << "Describe the transformation in words.\n";
		strstr << "\tExamples descriptions include:\n"
		"\tshift left 6 unit\n"
		"\tshift right 6 unit\n"
		"\tshift up 6 unit\n"
		"\tshift down 6 unit\n"
		"\thorizontal stretch by a factor of 5\n"
		"\thorizontal compression by a factor of 1/5\n"
		"\tvertical stretch by a factor of 5\n"
		"\tvertical compression by a factor of 1/5\n"
		"\tflip over the x-axis\n"
		"\tflip over the y-axis";
		break;
	case 1:
	default:
		strstr <<
		"Write out a mathematical formula that relates\n"
		"f(x) to g(x) if f(x) is g(x) after being\n";
		switch (transformation_choice) {
		case LR:
			answer = "g(x ";
			strstr << "shifted ";
			if (number < 0) {
				answer += "- ";
				answer += std::to_string(std::abs(number));
				strstr << "right ";
			} else {
				answer += "+ ";
				answer += std::to_string(number);
				strstr << "left ";
			}
			answer += ")";
			strstr << std::abs(number) << " unit";
			if (std::abs(number) != 1) {
				strstr << "s";
			}
			strstr << ".";
			break;
		case UD:
			answer = "g(x) ";
			strstr << "shifted ";
			if (number < 0) {
				answer += "- ";
				answer += std::to_string(std::abs(number));
				strstr << "down ";
			} else {
				answer += "+ ";
				answer += std::to_string(number);
				strstr << "up ";
			}
			strstr << std::abs(number) << " unit";
			if (std::abs(number) != 1) {
				strstr << "s";
			}
			strstr << ".";
			break;
		case HS:
			answer = "g(";
			strstr << "horizontally ";
			if (number < 0) {
				answer += "x / ";
				answer += std::to_string(std::abs(number));
				strstr << "stretched ";
			} else {
				answer += std::to_string(number);
				answer += " x";
				strstr << "compressed ";
			}
			answer += ")";
			strstr << "by a factor of ";
			if (number > 0) {
				strstr << "1/";
			}
			strstr << std::abs(number) << ".";
			break;
		case VS:
			strstr << "vertically ";
			if (number < 0) {
				answer = "(1/";
				answer += std::to_string(std::abs(number));
				answer += ") g(x)";
				strstr << "compressed ";
			} else {
				answer += std::to_string(number);
				answer += "g(x)";
				strstr << "stretched ";
			}
			strstr << "by a factor of ";
			if (number < 0) {
				strstr << "1/";
			}
			strstr << std::abs(number) << ".";
			break;
		case FL:
		default:
			strstr << "flipped over the ";
			if (number < 0) {
				answer = "-g(x)";
				strstr << "x";
			} else {
				answer = "g(-x)";
				strstr << "y";
			}
			strstr << "-axis.";
			break;
		}
		strstr <<
		"\n\tYour answer should be something like"
		"\n\tg(x - 5)"
		"\n\tg(x + 5)"
		"\n\tg(x) - 5"
		"\n\tg(x) + 5"
		"\n\tg(x / 5)"
		"\n\tg(5 x)"
		"\n\t2 g(x)"
		"\n\t(1/2) g(x)"
		"\n\t-g(x)"
		"\n\tg(-x)";
		break;
	}
	question = strstr.str();
	explanation += "I don't want to give a full explanation so here's the answer.";
	explanation += "\n\tAnswer: ";
	explanation += answer;
}

Question * Function_Transformations::make_copy(std::mt19937& gen) {
	return new Function_Transformations{gen};
}

QUESTION_STANDARD_DEFN(Function_Transformations)
