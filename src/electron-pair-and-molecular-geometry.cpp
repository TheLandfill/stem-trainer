#include "electron-pair-and-molecular-geometry.hpp"
#include <sstream>
#include <algorithm>
#include <cctype>
#include <string>

static const char * table[5][4]{
	{
		"linear"
	},
	{
		"trigonal planar",
		"bent"
	},
	{
		"tetrahedral",
		"trigonal pyramidal",
		"bent"
	},
	{
		"trigonal bipyramidal",
		"seesaw",
		"t-shaped",
		"linear"
	},
	{
		"octahedral",
		"square pyramidal",
		"square planar"
	}
};

Electron_Pair_And_Molecular_Geometry::Electron_Pair_And_Molecular_Geometry(std::mt19937& gen, size_t ster_num) : steric_number{ster_num} {
	change_vals(gen);
}

bool Electron_Pair_And_Molecular_Geometry::check_answer(const std::string& user_ans) {
	std::string user_ans_lower = user_ans;
	std::transform(user_ans_lower.begin(), user_ans_lower.end(), user_ans_lower.begin(), [](unsigned char c){ return std::tolower(c); });
	return user_ans_lower.compare(table[steric_number - 2][num_lone_pairs]) == 0;
}

void Electron_Pair_And_Molecular_Geometry::change_vals(std::mt19937& gen) {
	std::stringstream strstr;
	strstr << "| Electron Pair And Molecular Geometry |\n";
	static const size_t possible_num_lone_pairs[5]{
		0,
		1,
		2,
		3,
		2
	};
	std::uniform_int_distribution<size_t> num_lone_pairs_chooser{0, possible_num_lone_pairs[steric_number - 2]};
	num_lone_pairs = num_lone_pairs_chooser(gen);
	strstr << "An atom has " << steric_number - num_lone_pairs << " σ bonds and " << num_lone_pairs << " lone pairs.\nWhat is its molecular geometry?";
	question = strstr.str();
	explanation = table[steric_number - 2][num_lone_pairs];
}

Question * Electron_Pair_And_Molecular_Geometry::make_copy(std::mt19937& gen) {
	return new Electron_Pair_And_Molecular_Geometry{gen, steric_number};
}


QUESTION_STANDARD_DEFN(Electron_Pair_And_Molecular_Geometry)
