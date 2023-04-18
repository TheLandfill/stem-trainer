#pragma once
#include <string>
#include <random>

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
	virtual void add_correct() = 0;
	virtual void add_incorrect() = 0;
	virtual std::string get_topic_name() = 0;
};

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
	void add_correct() override; \
	void add_incorrect() override; \
	X(X&& x) noexcept = default; \
	virtual std::string get_topic_name() override; \
private: \
	std::string question; \
	std::string explanation; \
	static size_t correct; \
	static size_t incorrect;

#define QUESTION_STANDARD_DEFN(X) \
std::string X::get_question() { \
	return question; \
} \
\
std::string X::get_explanation() { \
	return explanation; \
} \
\
size_t X::num_correct() { \
	return correct; \
} \
\
size_t X::num_incorrect() { \
	return incorrect; \
} \
size_t X::num_worked() { \
	return correct + incorrect; \
} \
void X::add_correct() { \
	correct++; \
} \
void X::add_incorrect() { \
	incorrect++; \
} \
std::string X::get_topic_name() { \
	return #X; \
} \
size_t X::correct = 0; \
size_t X::incorrect = 0;
