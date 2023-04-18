#include "number-of-core-electrons.hpp"
#include "periodic-table.hpp"
#include <iostream>
#include <sstream>
#include <iomanip>

Number_Of_Core_Electrons::Number_Of_Core_Electrons(std::mt19937& gen) {
	change_vals(gen);
}

bool Number_Of_Core_Electrons::check_answer(const std::string& user_ans) {
	size_t user_num_ans;
	try {
		user_num_ans = std::stoul(user_ans);
	} catch(std::invalid_argument e) {
		return false;
	}
	return (user_num_ans == answer);
}

void Number_Of_Core_Electrons::change_vals(std::mt19937& gen) {
	size_t element = element_chooser(gen);
	std::stringstream strstr;
	strstr << "| Number of Core Electrons |:\n";
	strstr << "How many core electrons does " << element_symbols[element - 1] << " have?";
	answer = 0;
	for (size_t i = 0; i < 6; i++) {
		if (noble_gas_atomic_numbers[i] > element) {
			break;
		}
		answer = noble_gas_atomic_numbers[i];
	}
	question = strstr.str();
	explanation = "Find the number of electrons on the noble gas\n\tthat comes before the element.";
	explanation += "\n\tAnswer: ";
	explanation += std::to_string(answer);
}

Question * Number_Of_Core_Electrons::make_copy(std::mt19937& gen) {
	return new Number_Of_Core_Electrons{gen};
}

QUESTION_STANDARD_DEFN(Number_Of_Core_Electrons)
