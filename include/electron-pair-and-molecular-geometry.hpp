#pragma once
#include "question.hpp"

class Electron_Pair_And_Molecular_Geometry : public Question {
QUESTION_STANDARD_DECL(Electron_Pair_And_Molecular_Geometry)
public:
	Electron_Pair_And_Molecular_Geometry(std::mt19937& gen, size_t steric_number);
private:
	size_t steric_number;
	size_t num_lone_pairs;
};
