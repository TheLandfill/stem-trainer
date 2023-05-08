#include "unit-circle.hpp"

static const char * angles[2][16]{
	{
		"0°",
		"30°",
		"45°",
		"60°",
		"90°",
		"120°",
		"135°",
		"150°",
		"180°",
		"210°",
		"225°",
		"240°",
		"270°",
		"300°",
		"315°",
		"330°"
	},
	{
		"0",
		"π / 6",
		"π / 4",
		"π / 3",
		"π / 2",
		"2 π / 3",
		"3 π / 4",
		"5 π / 6",
		"π",
		"7 π / 6",
		"5 π / 4",
		"4 π / 3",
		"3 π / 2",
		"5 π / 3",
		"7 π / 4",
		"11 π / 6"
	}
};

// cos, sin, tan, sec, csc, cot
static const char * func_vals[3][16]{
	{
		"1",
		"sqrt(3)/2",
		"sqrt(2)/2",
		"1/2",
		"0",
		"-1/2",
		"-sqrt(2)/2",
		"-sqrt(3)/2",
		"-1",
		"-sqrt(3)/2",
		"-sqrt(2)/2",
		"-1/2",
		"0",
		"1/2",
		"sqrt(2)/2",
		"sqrt(3)/2",
	},
	{
		"0",
		"1/2",
		"sqrt(2)/2",
		"sqrt(3)/2",
		"1",
		"sqrt(3)/2",
		"sqrt(2)/2",
		"1/2",
		"0",
		"-1/2",
		"-sqrt(2)/2",
		"-sqrt(3)/2",
		"-1",
		"-sqrt(3)/2",
		"-sqrt(2)/2",
		"-1/2",
	},
	{
		"0",
		"sqrt(3)/3",
		"1",
		"sqrt(3)",
		"undef",
		"-sqrt(3)",
		"-1",
		"-sqrt(3)/3",
		"0",
		"sqrt(3)/3",
		"1",
		"sqrt(3)",
		"undef",
		"-sqrt(3)",
		"-1",
		"-sqrt(3)/3",
	}
};

static const char * func_names[3]{
	"cos",
	"sin",
	"tan",
};

Unit_Circle::Unit_Circle(std::mt19937& gen, size_t n) : which_func(n) {
	change_vals(gen);
}

bool Unit_Circle::check_answer(const std::string& user_ans) {
	return user_ans.compare(answer) == 0;
}

void Unit_Circle::change_vals(std::mt19937& gen) {
	size_t theta_choice = theta_chooser(gen);
	size_t rad_or_deg = rad_or_deg_dec(gen);
	question = "| Unit Circle |\nWhat is the exact value of ";
	question += func_names[which_func];
	question += "(";
	question += angles[rad_or_deg][theta_choice];
	question += ")?\n\nYour answer should\n\t- have no spaces\n\t- use sqrt(x) to indicate the square root of x\n\t- type \"undef\" if the answer is undefined.";
	answer = func_vals[which_func][theta_choice];
	explanation = "Answer: ";
	explanation += answer;
}

Question * Unit_Circle::make_copy(std::mt19937& gen) {
	return new Unit_Circle{gen, which_func};
}

QUESTION_STANDARD_DEFN(Unit_Circle)
