#include "question.hpp"

class Exponential_Growth_And_Decay : public Question {
QUESTION_STANDARD_DECL(Exponential_Growth_And_Decay)
public:
	enum PROBLEM_SCENARIO {
		INVESTMENT_INITIAL_VALUE = 0,
		INVESTMENT_VALUE_AFTER_TIME,
		INVESTMENT_CONTINUOUS_RATE,
		INVESTMENT_YEARLY_RATE,
		INVESTMENT_TIME_UNTIL_VALUE,
		SALARY_INCREASE_INITIAL_VALUE,
		SALARY_INCREASE_YEARLY_VALUE,
		SALARY_INCREASE_TIME_UNTIL_REACHES_VALUE,
		DRUG_DECREASE_INITIAL_VALUE,
		DRUG_DECREASE_CONTINUOUS_RATE,
		DRUG_DECREASE_HOURLY_RATE,
		DRUG_DECREASE_PERCENT_AFTER_TIME,
		DRUG_DECREASE_TIME_UNTIL_VALUE,
		RADIOACTIVE_DECAY_TIME_UNTIL_X_REMAINS,
		RADIOACTIVE_DECAY_CONTINUOUS_RATE_OF_DECAY,
		RADIOACTIVE_DECAY_YEARLY_RATE_OF_DECAY,
		COFFEE_TIME_UNTIL_REACHES_TEMPERATURE,
		COFFEE_INITIAL_TEMPERATURE,
		COFFEE_FINAL_TEMPERATURE,
	};
	Exponential_Growth_And_Decay(std::mt19937& gen, PROBLEM_SCENARIO min, PROBLEM_SCENARIO max);
	static const PROBLEM_SCENARIO unit_mins[];
	static const PROBLEM_SCENARIO unit_maxes[];
private:
	void investment_initial_value(std::mt19937& gen);
	void investment_value_after_time(std::mt19937& gen);
	void investment_continuous_rate(std::mt19937& gen);
	void investment_yearly_rate(std::mt19937& gen);
	void investment_time_until_value(std::mt19937& gen);
private:
	void salary_increase_initial_value(std::mt19937& gen);
	void salary_increase_yearly_value(std::mt19937& gen);
	void salary_increase_time_until_reaches_value(std::mt19937& gen);
private:
	void drug_decrease_initial_value(std::mt19937& gen);
	void drug_decrease_continuous_rate(std::mt19937& gen);
	void drug_decrease_hourly_rate(std::mt19937& gen);
	void drug_decrease_percent_after_time(std::mt19937& gen);
	void drug_decrease_time_until_value(std::mt19937& gen);
private:
	void radioactive_decay_time_until_x_remains(std::mt19937& gen);
	void radioactive_decay_continuous_rate_of_decay(std::mt19937& gen);
	void radioactive_decay_yearly_rate_of_decay(std::mt19937& gen);
private:
	void coffee_time_until_reaches_temperature(std::mt19937& gen);
	void coffee_initial_temperature(std::mt19937& gen);
	void coffee_final_temperature(std::mt19937& gen);
private:
	PROBLEM_SCENARIO min_prob, max_prob;
	std::uniform_int_distribution<size_t> scenario_chooser;
	double answer;
};

// Suppose a mg of a drug is injected into a person's bloodstream. As the drug
// is metabolized, the quantity diminishes [at the continuous rate of k% per
// hour/by b% every hour]?
// -   By what percent will the quantity of the drug decrease in one hour?
// -   We can model the quantity Q with the function Q(t) = a e^(k t). What is
// a?
// -   We can model the quantity Q with the function Q(t) = a e^(k t). What is
// k?
// -   We can model the quantity Q with the function Q(t) = a b^t. What is b?
// -   By what percent will the quantity of the drug decrease in X hours?
//
// If a radioactive substance decreases by 15% in 3 years,
// -   how long will it take until there is X% remaining?
// -   what is the continuous rate of decay?
// -   what is the yearly rate of decay?
//
// The function H = f(t) = 75 + 110 (0.90)^t represents the temperature of a
// cup of coffee, in degrees Fahrenheit, t minutes after it is poured.
// -   At what time will the temperature be 150°F?
// -   What is the initial temperature of the coffee?
// -   What will the final temperature of the coffee be?
//
// The function H = f(t) = 75 + 110 (0.90)^t represents the temperature of a
// pot of water, in degrees Fahrenheit, t minutes after it is put on the stove.
// -   How long will it take the water to boil (water boils at 212°F)?
//
// Suppose after graduation, you get a job that promises to give you pay
// increases of 4.5% each year. Your starting salary is $50,000.
// -   What is a in the formula ab^t or ae^(kt)?
// -   What is b in the formula ab^t?
// -   How many years until your salary reaches X?
