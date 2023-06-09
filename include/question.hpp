#pragma once
#include <string>
#include <sstream>
#include <cstdio>
#include <random>
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

class Question {
public:
	virtual ~Question() = default;
	virtual std::string get_question() = 0;
	virtual std::string get_explanation() = 0;
	virtual bool check_answer(const std::string& user_ans) = 0;
	virtual void change_vals(std::mt19937& gen) = 0;
	virtual Question* make_copy(std::mt19937& gen) = 0;
	virtual size_t num_correct() = 0;
	virtual size_t num_incorrect() = 0;
	virtual size_t num_worked() = 0;
	virtual size_t get_fudge_factor() = 0;
	virtual void add_correct() = 0;
	virtual void add_incorrect() = 0;
	virtual void add_fudge_factor() = 0;
	virtual std::string get_topic_name() = 0;
};

bool utf_print(FILE * out, std::stringstream& str);

#define QUESTION_STANDARD_DECL(X) \
public: \
	std::string get_question() override; \
	std::string get_explanation() override; \
	bool check_answer(const std::string& user_ans) override; \
	void change_vals(std::mt19937& gen) override; \
	Question * make_copy(std::mt19937& gen) override; \
	size_t num_correct() override; \
	size_t num_incorrect() override; \
	size_t num_worked() override; \
	size_t get_fudge_factor() override; \
	void add_correct() override; \
	void add_incorrect() override; \
	void add_fudge_factor() override; \
	X(X&& x) noexcept = default; \
	virtual std::string get_topic_name() override; \
private: \
	std::string question; \
	std::string explanation; \
	static size_t correct; \
	static size_t incorrect; \
	static size_t fudge_factor;

#define QUESTION_GET_QUESTION(X) \
std::string X::get_question() { \
	return question; \
}


#define QUESTION_GET_EXPLANATION(X) \
std::string X::get_explanation() { \
	return explanation; \
}

#define QUESTION_NUM_CORRECT(X) \
size_t X::num_correct() { \
	return correct; \
}

#define QUESTION_NUM_INCORRECT(X) \
size_t X::num_incorrect() { \
	return incorrect; \
}

#define QUESTION_NUM_WORKED(X) \
size_t X::num_worked() { \
	return correct + incorrect; \
}

#define QUESTION_GET_FUDGE_FACTOR(X) \
size_t X::get_fudge_factor() { \
	return fudge_factor; \
}

#define QUESTION_ADD_FUDGE_FACTOR(X) \
void X::add_fudge_factor() { \
	fudge_factor++; \
}

#define QUESTION_ADD_CORRECT(X) \
void X::add_correct() { \
	correct++; \
}

#define QUESTION_ADD_INCORRECT(X) \
void X::add_incorrect() { \
	incorrect++; \
}

#define QUESTION_GET_TOPIC_NAME(X) \
std::string X::get_topic_name() { \
	return #X; \
}

#define QUESTION_STANDARD_DEFN(X) \
QUESTION_GET_QUESTION(X) \
QUESTION_GET_EXPLANATION(X) \
QUESTION_NUM_CORRECT(X) \
QUESTION_NUM_INCORRECT(X) \
QUESTION_NUM_WORKED(X) \
QUESTION_GET_FUDGE_FACTOR(X) \
QUESTION_ADD_FUDGE_FACTOR(X) \
QUESTION_ADD_CORRECT(X) \
QUESTION_ADD_INCORRECT(X) \
QUESTION_GET_TOPIC_NAME(X) \
size_t X::correct = 0; \
size_t X::incorrect = 0; \
size_t X::fudge_factor = 1;
