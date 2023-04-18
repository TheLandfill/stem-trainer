#include "extract-info-from-trig.hpp"
#include <iostream>
#include <sstream>

Extract_Info_From_Trig_Function::Extract_Info_From_Trig_Function(std::mt19937& gen) {
	change_vals(gen);
}

bool Extract_Info_From_Trig_Function::check_answer(const std::string& user_ans) {
	return user_ans.compare(answer) == 0;
}

void Extract_Info_From_Trig_Function::change_vals(std::mt19937& gen) {
	int amplitude = val_chooser(gen);
	while (amplitude == 0) {
		amplitude = val_chooser(gen);
	}
	std::stringstream strstr;
	strstr << "Given the following trig function:\n";
	if (amplitude == -1) {
		strstr << "-";
	} else if (amplitude == 1) {
	} else {
		strstr << amplitude;
		strstr << " ";
	}
	amplitude = std::abs(amplitude);
	bool sin_func = sin_or_cos_chooser(gen);
	if (sin_func) {
		strstr << "sin(";
	} else {
		strstr << "cos(";
	}
	bool rational_period = rational_or_irrational_period_chooser(gen);
	int period = period_chooser(gen);
	if (rational_period) {
		if (period == 1) {
			strstr << "2πx";
		} else if (period % 2 == 0) {
			strstr << "πx/" << period / 2;
		} else {
			strstr << "2πx/" << period;
		}
	} else {
		if (period != 1) {
			strstr << period;
		}
		strstr << "x";
	}
	strstr << ")";
	int midline = val_chooser(gen);
	if (midline == 0) {

	} else if (midline < 0) {
		strstr << " - " << -midline;
	} else {
		strstr << " + " << midline;
	}
	strstr << "\nFind the ";
	size_t answer_choice = answer_chooser(gen);
	switch (answer_choice) {
	case 0:
		strstr << "period. Use 2pi/ω if necessary.";
		if (rational_period) {
			answer = std::to_string(period);
		} else {
			answer = "2pi/";
			answer += std::to_string(period);
		}
		explanation = "You should have divided 2π by what was\n"
		"\tmultiplying x inside the parentheses.";
		break;
	case 1:
		strstr << "amplitude.";
		answer = std::to_string(amplitude);
		explanation =
		"You should have looked at what was\n"
		"\tmultiplying the sine or cosine and\n"
		"\ttaken its absolute value.";
		break;
	case 2:
		strstr << "minimum value.";
		answer = std::to_string(midline - amplitude);
		explanation =
		"You should have subtracted the amplitude\n"
		"\tfrom the average value.";
		break;
	case 3:
		strstr << "maximum value.";
		answer = std::to_string(midline + amplitude);
		explanation =
		"You should have added the amplitude to the\n"
		"\taverage value.";
		break;
	case 4:
		strstr << "average value.";
		explanation =
		"You should have looked at the constant\n"
		"\tadded to the trig function.";
		answer = std::to_string(midline);
		break;
	case 5:
	default:
		strstr << "midline.";
		answer = "y=";
		answer += std::to_string(midline);
		explanation =
		"You should have \"y=(average)\".";
		break;
	}
	question = strstr.str();
	explanation += "\n\tAnswer: ";
	explanation += answer;
}

Question * Extract_Info_From_Trig_Function::make_copy(std::mt19937& gen) {
	return new Extract_Info_From_Trig_Function{gen};
}

QUESTION_STANDARD_DEFN(Extract_Info_From_Trig_Function)
