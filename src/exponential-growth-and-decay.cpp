#include "exponential-growth-and-decay.hpp"
#include <sstream>
#include <cmath>
#include <iomanip>

Exponential_Growth_And_Decay::Exponential_Growth_And_Decay(
	std::mt19937& gen,
	PROBLEM_SCENARIO min_choice,
	PROBLEM_SCENARIO max_choice
) : min_prob{min_choice},
	max_prob{max_choice},
	scenario_chooser{min_choice, max_choice}
{
	change_vals(gen);
}

bool Exponential_Growth_And_Decay::check_answer(const std::string& user_ans) {
	double user_num_ans;
	try {
		user_num_ans = std::stod(user_ans);
	} catch(std::invalid_argument e) {
		return false;
	}
	return (std::abs((user_num_ans - answer) / answer) <= 0.01);
}

void Exponential_Growth_And_Decay::change_vals(std::mt19937& gen) {
	PROBLEM_SCENARIO choice = static_cast<PROBLEM_SCENARIO>(scenario_chooser(gen));
	switch (choice) {
	case INVESTMENT_INITIAL_VALUE :
		investment_initial_value(gen);
		break;
	case INVESTMENT_VALUE_AFTER_TIME:
		investment_value_after_time(gen);
		break;
	case INVESTMENT_CONTINUOUS_RATE:
		investment_continuous_rate(gen);
		break;
	case INVESTMENT_YEARLY_RATE:
		investment_yearly_rate(gen);
		break;
	case INVESTMENT_TIME_UNTIL_VALUE:
		investment_time_until_value(gen);
		break;
	case SALARY_INCREASE_INITIAL_VALUE:
		salary_increase_initial_value(gen);
		break;
	case SALARY_INCREASE_YEARLY_VALUE:
		salary_increase_yearly_value(gen);
		break;
	case SALARY_INCREASE_TIME_UNTIL_REACHES_VALUE:
		salary_increase_time_until_reaches_value(gen);
		break;
	case DRUG_DECREASE_INITIAL_VALUE:
		drug_decrease_initial_value(gen);
		break;
	case DRUG_DECREASE_CONTINUOUS_RATE:
		drug_decrease_continuous_rate(gen);
		break;
	case DRUG_DECREASE_HOURLY_RATE:
		drug_decrease_hourly_rate(gen);
		break;
	case DRUG_DECREASE_PERCENT_AFTER_TIME:
		drug_decrease_percent_after_time(gen);
		break;
	case DRUG_DECREASE_TIME_UNTIL_VALUE:
		drug_decrease_time_until_value(gen);
		break;
	case RADIOACTIVE_DECAY_TIME_UNTIL_X_REMAINS:
		radioactive_decay_time_until_x_remains(gen);
		break;
	case RADIOACTIVE_DECAY_CONTINUOUS_RATE_OF_DECAY:
		radioactive_decay_continuous_rate_of_decay(gen);
		break;
	case RADIOACTIVE_DECAY_YEARLY_RATE_OF_DECAY:
		radioactive_decay_yearly_rate_of_decay(gen);
		break;
	case COFFEE_TIME_UNTIL_REACHES_TEMPERATURE:
		coffee_time_until_reaches_temperature(gen);
		break;
	case COFFEE_INITIAL_TEMPERATURE:
		coffee_initial_temperature(gen);
		break;
	case COFFEE_FINAL_TEMPERATURE:
		coffee_final_temperature(gen);
		break;
	}
}

Question * Exponential_Growth_And_Decay::make_copy(std::mt19937& gen) {
	return new Exponential_Growth_And_Decay{gen, min_prob, max_prob};
}
#define STR_CLEAR \
strstr.str(std::string{}); \
	strstr.clear();

#define INVESTMENT_MACRO \
std::stringstream strstr;\
	std::uniform_int_distribution yearly_rate_chooser{20, 70};\
	int yearly_rate = yearly_rate_chooser(gen);\
	std::uniform_int_distribution initial_value_chooser{40, 100};\
	int initial_value = initial_value_chooser(gen);\
	/* yearly, monthly, daily, continuous */ \
	std::uniform_int_distribution period_chooser{0, 3}; \
	int period = period_chooser(gen);\
	double period_list[4]{ 1.0, 12.0, 365.0, 1.0 }; \
	(void)period_list; \
	strstr << \
	"| Exponential Growth And Decay: Investment |\n" \
	"An account starts with $" << initial_value << ",000 and pays out at\n"\
	"a nominal yearly rate of " \
	<< std::fixed << std::setprecision(1) << (double)(yearly_rate) / 10.0 << "%.\nIf the interest is compounded "; \
	switch (period) {\
	case 0:\
		strstr << "per year";\
		break;\
	case 1:\
		strstr << "per month";\
		break;\
	case 2:\
		strstr << "per day";\
		break;\
	case 3:\
		strstr << "continuously";\
		break;\
	}\
	strstr << ",\n";

void Exponential_Growth_And_Decay::investment_initial_value(std::mt19937& gen) {
	INVESTMENT_MACRO
	strstr << "what is the value of the variable `a` in the formula I(t) = a ";
	if (period == 3) {
		strstr << "e^(k t)?";
	} else {
		strstr << "b^t?";
	}
	question = strstr.str();
	STR_CLEAR
	answer = initial_value * 1000;
	strstr <<
	"The variable `a` is the value of I(t) at t = 0, so it should be\n\t"
	"the initial value.\n\t"
	"Answer: " << initial_value << ",000";
	explanation = strstr.str();
}

void Exponential_Growth_And_Decay::investment_value_after_time(std::mt19937& gen) {
	INVESTMENT_MACRO
	std::uniform_int_distribution time_chooser{3, 20};
	int years_after_investment = time_chooser(gen);
	strstr << "what is the value of the account after " << years_after_investment << " years?\n"
	"Round to the nearest dollar.";
	question = strstr.str();
	STR_CLEAR
	answer = initial_value * 1000;
	strstr << "You should have used the formula\n\t\t";
	if (period == 3) {
		answer *= exp((double)(yearly_rate) * (double)(years_after_investment) / 1000.0);
		strstr << "I(t) = a e^(k t)\n\t"
		"where\n\t\t"
		"a = initial value = " << initial_value << ",000\n\t\t"
		"k = continuous rate = " << std::fixed << std::setprecision(3) << (double)(yearly_rate) / 1000.0 << "\n\t\t"
		"t = years after investment = " << years_after_investment;
	} else {
		answer *= pow(1.0 + (double)(yearly_rate) / 1000.0 / (period_list[period]), (double)(years_after_investment) * period_list[period]);
		strstr << "I(t) = a (1 + r / n)^(n t)\n\twhere\n\t\t" <<
		"a = initial value = " << initial_value << ",000\n\t\t"
		"r = yearly rate = " << std::fixed << std::setprecision(3) << (double)(yearly_rate) / 1000.0 << "\n\t\t"
		"n = number of times compounded per year = " << std::fixed << std::setprecision(0) << period_list[period] << "\n\t\t"
		"t = years after investment = " << years_after_investment;
	}
	strstr << "\n\tAnswer: " << std::fixed << std::setprecision(0) << answer;
	explanation = strstr.str();
}

void Exponential_Growth_And_Decay::investment_continuous_rate(std::mt19937& gen) {
	INVESTMENT_MACRO
	strstr << "what is the equivalent continuous rate?\n";
	strstr << "Round your answer to 4 sig figs.";
	question = strstr.str();
	STR_CLEAR
	if (period == 3) {
		answer = (double)(yearly_rate) / 1000.0;
		strstr << "It's just the nominal yearly rate.";
	} else {
		answer = 1.0 + (double)(yearly_rate) / 1000.0 / (period_list[period]);
		answer = log(answer);
		answer *= period_list[period];
		strstr <<
		"You should have converted the equation into the form\n\t\t"
		"I(t) = a b^t\n\t"
		"then converted to the form\n\t\t"
		"I(t) = a e^(k t)\n\t"
		"where your answer is k. If you did, you would get\n\t\t"
		"b = (1 + r / n)^n"
		"k = n ln(1 + r / n)";
	}
	strstr << "\n\tAnswer: " << std::defaultfloat << std::setprecision(5) << answer;
	explanation = strstr.str();
}

void Exponential_Growth_And_Decay::investment_yearly_rate(std::mt19937& gen) {
	INVESTMENT_MACRO
	strstr << "what is the equivalent yearly rate?\n";
	strstr << "Round your answer to 4 sig figs.";
	question = strstr.str();
	STR_CLEAR
	strstr << "You should have calculated\n\t\t";
	if (period == 3) {
		answer = exp(yearly_rate / 1000.0);
		strstr << "e^r - 1\n\t"
		"where\n\t\t"
		"r = nominal yearly rate = " << std::fixed << std::setprecision(3) << yearly_rate / 1000.0;
	} else {
		answer = pow(1.0 + (double)(yearly_rate) / 1000.0 / (period_list[period]), period_list[period]);
		strstr <<
		"(1 + r / n)^n - 1\n\t"
		"where\n\t\t"
		"r = nominal yearly rate = " << std::fixed << std::setprecision(3) << yearly_rate / 1000.0 << "\n\t\t"
		"n = number of times compounded / year = " << std::fixed << std::setprecision(0) << period_list[period];
	}
	answer -= 1.0;
	strstr << "\n\tAnswer: " << std::defaultfloat << std::setprecision(5) << answer;
	explanation = strstr.str();
}

void Exponential_Growth_And_Decay::investment_time_until_value(std::mt19937& gen) {
	INVESTMENT_MACRO
	std::uniform_int_distribution final_value_chooser{(int)(initial_value * 1.5), initial_value * 2};
	int final_value = final_value_chooser(gen);
	strstr <<
	"How many years will you have to wait before the account has\n"
	"at least $" << final_value << ",000?\n" <<
	"Round your answer up to the nearest whole number.";
	question = strstr.str();
	STR_CLEAR
	strstr
	<< "You should have solved the equation I(t) = " << final_value << ",000.\n\t"
	"More specifically, you should have solved\n\t\t";
	answer = log((double)(final_value) / (double)(initial_value));
	if (period == 3) {
		answer /= (double)(yearly_rate) / 1000.0;
		strstr << "f = a e^(k t)\n\t"
		"where\n\t\t"
		"a = initial value = " << initial_value << ",000\n\t\t"
		"k = continuous rate = " << std::fixed << std::setprecision(3) << (double)(yearly_rate) / 1000.0 << "\n\t\t"
		"f = final value = " << final_value << ",000";
	} else {
		answer /= log(1.0 + (double)(yearly_rate) / 1000.0 / (period_list[period]));
		answer /= period_list[period];
		strstr << "f = a (1 + r / n)^(n t)\n\twhere\n\t\t" <<
		"for t, where\n\t\t"
		"a = initial value = " << initial_value << ",000\n\t\t"
		"r = nominal yearly rate = " << std::fixed << std::setprecision(3) << yearly_rate / 1000.0 << "\n\t\t"
		"n = number of times compounded per year = " << std::fixed << std::setprecision(0) << period_list[period] << "\n\t\t"
		"f = final value = " << final_value << ",000";
	}
	answer = ceil(answer);
	strstr << "\n\tAnswer: " << std::fixed << std::setprecision(0) << answer;
	explanation = strstr.str();
}

#define SALARY_MACRO \
std::stringstream strstr;\
	std::uniform_int_distribution yearly_rate_chooser{20, 100};\
	int yearly_rate = yearly_rate_chooser(gen);\
	std::uniform_int_distribution initial_salary_chooser{40, 100};\
	int initial_salary = initial_salary_chooser(gen);\
	strstr <<\
	"| Exponential Growth And Decay: Salary |\n" \
	"Suppose after graduation, you get a job that promises to give you\n"\
	"pay increases of " << std::fixed << std::setprecision(1) << (double)(yearly_rate) / 10.0 << "\% each year. Your starting salary is $" << initial_salary << ",000 per year.\n";

void Exponential_Growth_And_Decay::salary_increase_initial_value(std::mt19937& gen) {
	SALARY_MACRO
	std::uniform_int_distribution continuous_or_yearly_chooser{0, 1};
	int continuous_rate = continuous_or_yearly_chooser(gen);
	strstr <<
	"What would the variable `a` be if you were to model your salary with\n"
	"the formula S(t) = a ";
	if (continuous_rate) {
		strstr << "e^(k t)?";
	} else {
		strstr << "b^t?";
	}
	question = strstr.str();
	STR_CLEAR
	answer = initial_salary * 1000;
	strstr <<
	"The variable `a` is the value of S(t) at t = 0, so it should be\n\t"
	"the initial salary.\n\t"
	"Answer: " << initial_salary << ",000";
	explanation = strstr.str();
}

void Exponential_Growth_And_Decay::salary_increase_yearly_value(std::mt19937& gen) {
	SALARY_MACRO
	strstr <<
	"What would the variable `b` be if you were to model your salary with\n"
	"the formula S(t) = a b^t?";
	question = strstr.str();
	STR_CLEAR
	strstr << "You should have calculated (1 + r) where r is a decimal.\n\t";
	answer = 1000 + yearly_rate;
	answer /= 1000.0;
	strstr << "Answer: " << std::setprecision(3) << answer;
	explanation = strstr.str();
}

void Exponential_Growth_And_Decay::salary_increase_time_until_reaches_value(std::mt19937& gen) {
	SALARY_MACRO
	std::uniform_int_distribution final_salary_chooser{(int)(initial_salary * 1.5), initial_salary * 2};
	int final_salary = final_salary_chooser(gen);
	strstr <<
	"How many years will you have to wait before you make at\n"
	"least $" << final_salary << ",000 per year?\n" <<
	"Round your answer up to the nearest whole number.";
	question = strstr.str();
	STR_CLEAR
	strstr <<
	"You should have solved the equation S(t) = " << final_salary << ",000.\n\t"
	"More specifically, you should have solved\n\t\t"
	<< initial_salary << ",000 " << "(1.00 + " << std::fixed << std::setprecision(3) << (double)(yearly_rate) / 1000.0 << ")^t = " << final_salary << ",000";
	answer = (double)(final_salary) / (double)(initial_salary);
	answer = log(answer);
	answer /= log(1.0 + (double)(yearly_rate) / 1000.0);
	answer = ceil(answer);
	strstr << "\n\tAnswer: " << std::fixed << std::setprecision(0) << answer;
	explanation = strstr.str();
}

#define DRUG_DECREASE_MACRO \
std::stringstream strstr; \
	std::uniform_int_distribution initial_value_chooser{2, 10}; \
	int initial_value = initial_value_chooser(gen); \
	std::uniform_int_distribution decay_rate_chooser{1, 10}; \
	int decay_rate_percent = decay_rate_chooser(gen); \
	double continuous_decay_rate = -decay_rate_percent; \
	continuous_decay_rate /= 100.0; \
	(void)continuous_decay_rate; \
	strstr <<\
	"| Exponential Growth And Decay: Medicine |\n" \
	"Suppose " << initial_value << " mg of a drug is injected into a person's\n" \
	"bloodstream. As the drug is metabolized, the quantity diminishes\n" \
	"at a continuous rate of " << decay_rate_percent << "\% per hour.\n";

void Exponential_Growth_And_Decay::drug_decrease_initial_value(std::mt19937& gen) {
	DRUG_DECREASE_MACRO
	strstr << "What is the value of the variable `a` in the formula\n"
	"Q(t) = a ";
	std::uniform_int_distribution continuous_or_hourly_chooser{0, 1};
	int continuous_or_hourly = continuous_or_hourly_chooser(gen);
	if (continuous_or_hourly) {
		strstr << "e^(k t)?";
	} else {
		strstr << "b^t?";
	}
	strstr << "\nRound to three sig figs.";
	question = strstr.str();
	STR_CLEAR
	answer = initial_value;
	strstr <<
	"The variable `a` is the value of Q(t) at t = 0, so it should be\n\t"
	"the initial value.\n\t"
	"Answer: " << answer;
	explanation = strstr.str();
}

void Exponential_Growth_And_Decay::drug_decrease_continuous_rate(std::mt19937& gen) {
	DRUG_DECREASE_MACRO
	strstr <<
	"What is the value of the variable `k` in the formula\n\t"
	"Q(t) = a e^(k t)?\n"
	"Round to three sig figs.";
	question = strstr.str();
	answer = continuous_decay_rate;
	STR_CLEAR
	strstr <<
	"It's just the continuous decay rate made negative so\n\t"
	"the amount decays over time.\n\t"
	"Answer: " << continuous_decay_rate;
	explanation = strstr.str();
}

void Exponential_Growth_And_Decay::drug_decrease_hourly_rate(std::mt19937& gen) {
	DRUG_DECREASE_MACRO
	strstr <<
	"What is the value of the variable `b` in the formula\n\t"
	"Q(t) = a b^t?\n"
	"Round to three sig figs.";
	question = strstr.str();
	STR_CLEAR
	answer = exp(continuous_decay_rate);
	strstr <<
	"You should have calculated e^k, where k is the continuous rate.\n\t"
	"Answer: " << answer;
	explanation = strstr.str();
}

void Exponential_Growth_And_Decay::drug_decrease_percent_after_time(std::mt19937& gen) {
	DRUG_DECREASE_MACRO
	std::uniform_int_distribution num_hours_chooser{1, 7};
	int num_hours = num_hours_chooser(gen);
	strstr << "How much of the drug would be left after " << num_hours << " hours?\n"
	"Round to three sig figs.";
	question = strstr.str();
	STR_CLEAR
	answer = (double)(initial_value) * exp(continuous_decay_rate * (double)(num_hours));
	strstr << "You should have used the formula\n\t\t"
	"Q(t) = a e^(k t)\n\t"
	"where\n\t\t"
	"a = initial amount = " << initial_value << "\n\t\t"
	"k = continuous decay rate = " << continuous_decay_rate << "\n\t\t"
	"t = time in hours after injection = " << num_hours << "\n\t"
	"Answer: " << answer;
	explanation = strstr.str();
}

void Exponential_Growth_And_Decay::drug_decrease_time_until_value(std::mt19937& gen) {
	DRUG_DECREASE_MACRO
	std::uniform_int_distribution final_value_chooser{ initial_value * 10, initial_value * 75 };
	double final_value = final_value_chooser(gen);
	final_value /= 100.0;
	strstr << "How long until " << std::fixed << std::setprecision(2) << final_value << " mg remains in\n"
	"the blood stream? Round to three sig figs.";
	question = strstr.str();
	STR_CLEAR
	answer = log(final_value / (double)(initial_value)) / continuous_decay_rate;
	strstr << "You should have solved the equation Q(t) = " << final_value << ".\n\t"
	"More specifically, you should have solved\n\t\t"
	"f = a e^(k t)\n\t"
	"for t, where\n\t\t"
	"a = initial amount = " << initial_value << "\n\t\t"
	"k = continuous decay rate = " << continuous_decay_rate << "\n\t\t"
	"f = final value = " << final_value << "\n\t"
	"Answer: " << std::defaultfloat << std::setprecision(3) << answer;
	explanation = strstr.str();
}

#define RADIOACTIVE_DECAY_MACRO \
std::stringstream strstr;\
	std::uniform_int_distribution period_chooser{1, 5};\
	int period = period_chooser(gen);\
	std::uniform_int_distribution decay_rate_over_period_chooser{1, 5 * period};\
	int decay_rate_over_period = decay_rate_over_period_chooser(gen);\
	strstr <<\
	"| Exponential Growth And Decay: Radioactive Decay |\n" \
	"If a radioactive substance decreases by " << decay_rate_over_period << "\% every "\
	<< period << " year";\
	if (period != 1) {\
		strstr << "s";\
	}\
	strstr << ",\n";

void Exponential_Growth_And_Decay::radioactive_decay_time_until_x_remains(std::mt19937& gen) {
	RADIOACTIVE_DECAY_MACRO
	std::uniform_int_distribution percent_remaining_chooser{25, 90};
	int percent_remaining = percent_remaining_chooser(gen);
	strstr <<
	"how long will it take until there is " << percent_remaining << "\% remaining?\n";
	strstr << "You shouldn't need to know the initial quantity of the substance.\n";
	strstr << "Round your final answer to 4 sig figs.";
	question = strstr.str();
	STR_CLEAR
	answer =
		(double)period *
		log((double)(percent_remaining) / 100.0)
		/
		log(1.0 - (
				(double)(decay_rate_over_period) / 100.0
			)
		);
	strstr << "You should have solved the equation\n\t\t"
	"(initial amount) (rate)^(t/(num years)) = (final amount)\n\t"
	"where\n\t\t"
	"(final amount) / (initial amount) = 0.";
	if (percent_remaining < 10) {
		strstr << "0";
	}
	strstr << percent_remaining << "\n\t\t"
	"(rate) = 1.0 - 0.";
	if (decay_rate_over_period < 10) {
		strstr << "0";
	}
	strstr << std::fixed << std::setprecision(2) <<
	decay_rate_over_period << "\n\t\t"
	"(num years) = " << period << "\n\t";
	strstr << "Answer: " << std::defaultfloat << std::setprecision(5) << answer;
	explanation = strstr.str();
}

void Exponential_Growth_And_Decay::radioactive_decay_continuous_rate_of_decay(std::mt19937& gen) {
	RADIOACTIVE_DECAY_MACRO
	strstr << "what is the continuous rate of decay?\n";
	strstr << "You shouldn't need to know the initial quantity of the substance.\n";
	strstr << "Round your final answer to 4 sig figs.";
	question = strstr.str();
	STR_CLEAR
	strstr << "You should have converted the equation from the form\n\t\t"
	"Q(t) = a b^(t / p)" "\n\tto\n\t\t"
	"Q(t) = a e^(k t)\n\t"
	"and found k, which you can do using\n\t\t"
	"b^(t / p) = e^(ln(b) t / p)\n\t"
	"which implies k = ln(b) / p, where\n\t\t"
	"k = continuous rate of decay\n\t\t"
	"b = 1.00 - " << std::fixed << std::setprecision(2) << (double)(decay_rate_over_period) / 100.0 << "\n\t\t"
	"p = " << period;
	answer = log(1.0 - (double)(decay_rate_over_period) / 100.0);
	answer /= (double)period;
	strstr << "\n\tAnswer: " << std::defaultfloat << std::setprecision(5) << answer;
	explanation = strstr.str();
}

void Exponential_Growth_And_Decay::radioactive_decay_yearly_rate_of_decay(std::mt19937& gen) {
	RADIOACTIVE_DECAY_MACRO
	strstr << "what is the yearly rate of decay?\n";
	strstr << "You shouldn't need to know the initial quantity of the substance.\n";
	strstr << "Round your final answer to 4 sig figs.";
	question = strstr.str();
	STR_CLEAR
	answer = pow(1.0 - (double)(decay_rate_over_period) / 100.0, 1.0 / (double)(period));
	strstr << "You should have converted the equation from the form\n\t\t"
	"Q(t) = a r^(t / p)\n\t"
	"to\n\t\t"
	"Q(t) = a b^t\n\t"
	"which means b = r^(1 / p) where\n\t\t"
	"r = 1.00 - " << std::fixed << std::setprecision(2) << (double)(decay_rate_over_period) / 100.0 << "\n\t\t"
	"p = " << period;
	strstr << "\n\tAnswer: " << std::defaultfloat << std::setprecision(5) << answer;
	explanation = strstr.str();
}

#define COFFEE_MACRO \
std::stringstream strstr;\
	std::uniform_int_distribution final_temp_chooser{60, 80};\
	int final_temp = final_temp_chooser(gen);\
	std::uniform_int_distribution initial_temp_chooser{160, 200};\
	int initial_temp = initial_temp_chooser(gen);\
	std::uniform_int_distribution decay_rate_chooser{60, 95};\
	int decay_rate = decay_rate_chooser(gen);\
	int temp_diff = initial_temp - final_temp; \
	strstr <<\
	"| Exponential Growth And Decay: Newton's Law of Cooling |\n" \
	"The function\n"\
	"\tT(t) = " << final_temp << " + " << temp_diff << " (0." << decay_rate << ")^t\n"\
	"represents the temperature of a cup of coffee, in degrees\n"\
	"Fahrenheit, t minutes after it is poured.\n";

void Exponential_Growth_And_Decay::coffee_time_until_reaches_temperature(std::mt19937& gen) {
	COFFEE_MACRO
	int temp_diff_scale = temp_diff;
	temp_diff_scale /= 4;
	std::uniform_int_distribution desired_temp_chooser{final_temp + temp_diff_scale, initial_temp - temp_diff_scale};
	int desired_temp = desired_temp_chooser(gen);
	strstr << "How many minutes after it is poured will it reach the\n"
	"temperature "<< desired_temp << "°F?";
	answer = log(
		(double)(desired_temp - final_temp)
		/
		(double)temp_diff
	) / log(
		(double)(decay_rate)
		/
		100.0
	);
	question = strstr.str();
	STR_CLEAR
	strstr << "Solve the equation T(t) = " << desired_temp << ". More specifically,\n\tSolve the equation\n\t\t";
	strstr <<
	final_temp << " + " << temp_diff << " (0." << decay_rate << ")^t = "
	<< desired_temp << "\n\tfor t.\n";
	strstr << "\tAnswer: " << answer;
	explanation = strstr.str();
}

void Exponential_Growth_And_Decay::coffee_initial_temperature(std::mt19937& gen) {
	COFFEE_MACRO
	strstr << "What was the initial temperature of the coffee?";
	answer = initial_temp;
	question = strstr.str();
	STR_CLEAR
	strstr <<
	"The initial temperature is given at t = 0, which means\n"
	"T(0) = " << final_temp << " + " << temp_diff << " (0." << decay_rate <<
	")^0 = " << final_temp << " + " << temp_diff << " (1) = " <<
	final_temp << " + " << temp_diff << " = " << initial_temp << "\n\t";
	strstr << "Answer: " << answer;
	explanation = strstr.str();
}

void Exponential_Growth_And_Decay::coffee_final_temperature(std::mt19937& gen) {
	COFFEE_MACRO
	strstr << "What will the temperature of the coffee be after it\n"
	"has sat out for a long time in degrees Fahrenheit?";
	answer = final_temp;
	question = strstr.str();
	STR_CLEAR
	strstr <<
	"After a long period of time, the exponential part\n\t"
	"will go to zero, leaving you with\n\t"
	"T(∞) = " << final_temp << " + " << temp_diff << " (0." << decay_rate << ")^∞ = " << final_temp << " + 0 = " << final_temp << "\n\t";
	strstr << "Answer: " << answer;
	explanation = strstr.str();
}

const Exponential_Growth_And_Decay::PROBLEM_SCENARIO Exponential_Growth_And_Decay::unit_mins[]{
	Exponential_Growth_And_Decay::INVESTMENT_INITIAL_VALUE,
	Exponential_Growth_And_Decay::SALARY_INCREASE_INITIAL_VALUE,
	Exponential_Growth_And_Decay::DRUG_DECREASE_INITIAL_VALUE,
	Exponential_Growth_And_Decay::RADIOACTIVE_DECAY_TIME_UNTIL_X_REMAINS,
	Exponential_Growth_And_Decay::COFFEE_TIME_UNTIL_REACHES_TEMPERATURE,
};

const Exponential_Growth_And_Decay::PROBLEM_SCENARIO Exponential_Growth_And_Decay::unit_maxes[]{
	Exponential_Growth_And_Decay::INVESTMENT_TIME_UNTIL_VALUE,
	Exponential_Growth_And_Decay::SALARY_INCREASE_TIME_UNTIL_REACHES_VALUE,
	Exponential_Growth_And_Decay::DRUG_DECREASE_TIME_UNTIL_VALUE,
	Exponential_Growth_And_Decay::RADIOACTIVE_DECAY_YEARLY_RATE_OF_DECAY,
	Exponential_Growth_And_Decay::COFFEE_FINAL_TEMPERATURE,
};

#undef QUESTION_ADD_FUDGE_FACTOR
#define QUESTION_ADD_FUDGE_FACTOR(X)

void Exponential_Growth_And_Decay::add_fudge_factor() {
	fudge_factor += 2;
}

QUESTION_STANDARD_DEFN(Exponential_Growth_And_Decay)
