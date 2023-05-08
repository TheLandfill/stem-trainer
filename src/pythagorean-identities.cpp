#include "pythagorean-identities.hpp"

static const char * identity_question[9]{
	"sin²(x) + cos²(x)", // = 1
	"1 + cot²(x)", // = csc²(x)
	"tan²(x) + 1", // = sec²(x)
	"1 - sin²(x)", // = cos²(x)
	"1 - cos²(x)", // = sin²(x)
	"csc²(x) - 1", // = cot²(x)
	"csc²(x) - cot²(x)", // = 1
	"sec²(x) - 1", // = tan²(x)
	"sec²(x) - tan²(x)", // = 1
};

static const char * identity_answers[9]{
	"1",
	"csc^2(x)",
	"sec^2(x)",
	"cos^2(x)",
	"sin^2(x)",
	"cot^2(x)",
	"1",
	"tan^2(x)",
	"1",
};

Pythagorean_Identities::Pythagorean_Identities(std::mt19937& gen) {
	change_vals(gen);
}

bool Pythagorean_Identities::check_answer(const std::string& user_ans) {
	return user_ans.compare(answer) == 0;
}

void Pythagorean_Identities::change_vals(std::mt19937& gen) {
	which_identity = identity_chooser(gen);
	question = "| Pythagorean Identities |\nWhat is the exact value of ";
	question += identity_question[which_identity];
	question += "?\n\nYour answer should\n\t- have no spaces\n\t- use x^2 to indicate the square of x\n\t- Only consist of a trig function squared or 1.";
	answer = identity_answers[which_identity];
	explanation = "Start with the equation sin²(x) + cos²(x) = 1.\n\t"
	"If the problem has sec²(x) or tan²(x), divide the equation by cos²(x).\n\t"
	"If the problem has csc²(x) or cot²(x), divide the equation by sin²(x).\n\t"
	"If you see a - in the problem, subtract the negative term from both sides of the equation.\n\t"
	"One side of the equation will have the expression in the problem.\n\t"
	"The other side of the equation is your solution.\n\t"
	"Answer: ";
	explanation += answer;
}

Question * Pythagorean_Identities::make_copy(std::mt19937& gen) {
	return new Pythagorean_Identities{gen};
}

QUESTION_STANDARD_DEFN(Pythagorean_Identities)
