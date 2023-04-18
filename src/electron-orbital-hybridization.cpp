#include "electron-orbital-hybridization.hpp"
#include <sstream>
#include <algorithm>
#include <cctype>
#include <string>

static const char * table[7]{
	"s",
	"sp",
	"sp^2",
	"sp^3",
	"sp^3d",
	"sp^3d^2",
	"sp^3d^3",
};

Electron_Orbital_Hybridization::Electron_Orbital_Hybridization(std::mt19937& gen) {
	change_vals(gen);
}

bool Electron_Orbital_Hybridization::check_answer(const std::string& user_ans) {
	std::string user_ans_lower = user_ans;
	std::transform(user_ans_lower.begin(), user_ans_lower.end(), user_ans_lower.begin(), [](unsigned char c){ return std::tolower(c); });
	return user_ans_lower.compare(table[steric_number - 1]) == 0;
}

void Electron_Orbital_Hybridization::change_vals(std::mt19937& gen) {
	std::stringstream strstr;
	strstr << "| Electron Orbital Hybridization |\n";
	steric_number = steric_number_chooser(gen);
	static const size_t possible_num_lone_pairs[6]{
		0,
		0,
		1,
		2,
		3,
		2
	};
	std::uniform_int_distribution<size_t> num_lone_pairs_chooser{0, possible_num_lone_pairs[steric_number - 2]};
	size_t num_lone_pairs = num_lone_pairs_chooser(gen);
	strstr << "An atom has " << steric_number - num_lone_pairs << " σ bonds and " << num_lone_pairs << " lone pairs.\nWhat is its electron hybridization?\nYour answer should look like sp^3.";
	question = strstr.str();
	explanation = table[steric_number - 1];
}

Question * Electron_Orbital_Hybridization::make_copy(std::mt19937& gen) {
	return new Electron_Orbital_Hybridization{gen};
}

QUESTION_STANDARD_DEFN(Electron_Orbital_Hybridization)
