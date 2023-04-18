#include "change-in-internal-energy-work-and-heat.hpp"
#include <iostream>
#include <sstream>
#include <iomanip>

Change_In_Internal_Energy_Work_And_Heat::Change_In_Internal_Energy_Work_And_Heat(std::mt19937& gen) {
	change_vals(gen);
}

bool Change_In_Internal_Energy_Work_And_Heat::check_answer(const std::string& user_ans) {
	double user_num_ans;
	try {
		user_num_ans = std::stod(user_ans);
	} catch(std::invalid_argument e) {
		return false;
	}
	return (
		(std::abs(user_num_ans - answer) / answer) <= 0.01
	);
}

void Change_In_Internal_Energy_Work_And_Heat::change_vals(std::mt19937& gen) {
	std::stringstream strstr;
	double work_done_on_environment = energy_chooser(gen);
	while (work_done_on_environment == 0) {
		work_done_on_environment = energy_chooser(gen);
	}
	work_done_on_environment *= 10.0;
	double heat_given_to_environment = energy_chooser(gen);
	while (heat_given_to_environment == 0) {
		heat_given_to_environment = energy_chooser(gen);
	}
	strstr << "| Change in Internal Energy Given Heat and Work |\n";
	strstr << "What is the change in energy of a system that ";
	if (heat_given_to_environment < 0) {
		strstr << "absorbs " << -heat_given_to_environment << " kJ in heat from the environment";
	} else {
		strstr << "gives off " << heat_given_to_environment << " kJ in heat to the environment";
	}
	strstr << "\nand\n";
	if (work_done_on_environment < 0) {
		strstr << "whose surroundings performs " << -work_done_on_environment << " J of work on it?";
	} else {
		strstr << "performs " << work_done_on_environment << " J of work on its surroundings?";
	}
	strstr << "\nGive your answer in kJ.";
	answer = -heat_given_to_environment - work_done_on_environment / 1000.0;
	question = strstr.str();
	strstr.str(std::string{});
	strstr.clear();
	strstr <<
	"If the object is giving off heat, it's losing energy,\n\t"
	"so we should subtract the heat energy off. If the object\n\t"
	"is being heated by the environment, it's gaining energy,\n\t"
	"so we add the heat energy. Likewise, if the object is\n\t"
	"doing work on its environment, it's losing energy, so we\n\t"
	"subtract the work energy. If the environment is doing\n\t"
	"work on the object, it's gaining energy so we add the\n\t"
	"energy. In this case, you should have\n\t"
	<< -heat_given_to_environment << " kJ";
	if (work_done_on_environment < 0) {
		strstr << " + " << -work_done_on_environment;
	} else {
		strstr << " - " << work_done_on_environment;
	}
	strstr << " J\n\t"
	"Note that the work is in J, so we need to divide it by 1000."
	"\n\tAnswer: " << std::fixed << std::setprecision(3) << answer;
	explanation = strstr.str();
}

Question * Change_In_Internal_Energy_Work_And_Heat::make_copy(std::mt19937& gen) {
	return new Change_In_Internal_Energy_Work_And_Heat{gen};
}

QUESTION_STANDARD_DEFN(Change_In_Internal_Energy_Work_And_Heat)
