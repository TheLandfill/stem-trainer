#include "inverse-unit-circle.hpp"

static const char * angles[2][16]{
	{
		"-150",
		"-135",
		"-120",
		"-90",
		"-60",
		"-45",
		"-30",
		"0",
		"30",
		"45",
		"60",
		"90",
		"120",
		"135",
		"150",
		"180",
	},
	{
		"-5pi/6",
		"-3pi/4",
		"-2pi/3",
		"-pi/2",
		"-pi/3",
		"-pi/4",
		"-pi/6",
		"0",
		"pi/6",
		"pi/4",
		"pi/3",
		"pi/2",
		"2pi/3",
		"3pi/4",
		"5pi/6",
		"pi",
	}
};

// cos, sin, tan, sec, csc, cot
static const char * func_vals[2][9]{
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
	},
	{
		"undef",
		"-sqrt(3)",
		"-1",
		"-sqrt(3)/3",
		"0",
		"sqrt(3)/3",
		"1",
		"sqrt(3)",
		"undef"
	}
};

static const char * func_names[3]{
	"sin",
	"cos",
	"tan",
};

static const char * rad_or_deg_name[2]{
	"degrees",
	"radians",
};

Inverse_Unit_Circle::Inverse_Unit_Circle(std::mt19937& gen, size_t n) : which_func(n) {
	change_vals(gen);
}

bool Inverse_Unit_Circle::check_answer(const std::string& user_ans) {
	return user_ans.compare(answer) == 0;
}

void Inverse_Unit_Circle::change_vals(std::mt19937& gen) {
	size_t theta_choice = theta_chooser(gen);
	while (which_func == 2 && (theta_choice == 0 || theta_choice == 8)) {
		theta_choice = theta_chooser(gen);
	}
	size_t rad_or_deg = rad_or_deg_dec(gen);
	size_t val_to_use[3]{ 0, 0, 1 };
	question = "| Inverse Unit Circle |\nWhat is the exact value of arc";
	question += func_names[which_func];
	question += "(";
	question += func_vals[val_to_use[which_func]][theta_choice];
	question += ") in ";
	question += rad_or_deg_name[rad_or_deg];
	question += "?\n\nYour answer should\n\t- have no spaces\n\t- use pi to indicate π\n\t- not use any units.";
	switch (which_func) {
	case 0:
		answer = angles[rad_or_deg][3 + (8 - theta_choice)];
		break;
	case 1:
		answer = angles[rad_or_deg][theta_choice + 7];
		break;
	case 2:
		answer = angles[rad_or_deg][3 + theta_choice];
	}
	explanation = "Answer: ";
	explanation += answer;
}

Question * Inverse_Unit_Circle::make_copy(std::mt19937& gen) {
	return new Inverse_Unit_Circle{gen, which_func};
}

QUESTION_STANDARD_DEFN(Inverse_Unit_Circle)
