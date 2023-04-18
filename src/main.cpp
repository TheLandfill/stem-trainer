#include "all-questions.hpp"
#include <random>
#include <iostream>
#include <vector>
#include <memory>
#include <algorithm>
#include <queue>

int main() {
	std::random_device rd;
	std::mt19937 gen{rd()};
	size_t min_num_correct = 3;
	size_t total_number_of_questions_answered = 0;
	std::vector<std::vector<std::unique_ptr<Question>>> unit_topics;
	unit_topics.emplace_back();
	unit_topics.back().emplace_back(new Pythagorean_Theorem{gen});
	unit_topics.emplace_back();
	unit_topics.back().emplace_back(new Pythagorean_Identities{gen});
	// unit_topics.emplace_back();
	// unit_topics.back().emplace_back(new Radians_To_Degrees{gen});
	// unit_topics.emplace_back();
	// unit_topics.back().emplace_back(new Polar_And_Cartesian{gen});
	// unit_topics.emplace_back();
	// unit_topics.back().emplace_back(new Arc_Length_And_Angles{gen});
	// unit_topics.emplace_back();
	// unit_topics.back().emplace_back(new Two_Sides_All_Trig{gen});
	// unit_topics.emplace_back();
	// unit_topics.back().emplace_back(new Simple_Trig{gen});
	// unit_topics.emplace_back();
	// unit_topics.back().emplace_back(new Point_From_Angle_And_Other_Point{gen});
	// unit_topics.emplace_back();
	// unit_topics.back().emplace_back(new Unit_Circle{gen, 0});
	// unit_topics.emplace_back();
	// unit_topics.back().emplace_back(new Unit_Circle{gen, 1});
	// unit_topics.emplace_back();
	// unit_topics.back().emplace_back(new Unit_Circle{gen, 2});
	// unit_topics.emplace_back();
	// unit_topics.back().emplace_back(new Inverse_Unit_Circle{gen, 0});
	// unit_topics.emplace_back();
	// unit_topics.back().emplace_back(new Inverse_Unit_Circle{gen, 1});
	// unit_topics.emplace_back();
	// unit_topics.back().emplace_back(new Inverse_Unit_Circle{gen, 2});
	// unit_topics.emplace_back();
	// unit_topics.back().emplace_back(new Sine_Cosine_Range_Amplitude_Midline{gen});
	// unit_topics.emplace_back();
	// unit_topics.back().emplace_back(new Extract_Info_From_Trig_Function{gen});
	// unit_topics.emplace_back();
	// unit_topics.back().emplace_back(new Electron_Pair_And_Molecular_Geometry{gen, 2});
	// unit_topics.emplace_back();
	// unit_topics.back().emplace_back(new Electron_Pair_And_Molecular_Geometry{gen, 3});
	// unit_topics.emplace_back();
	// unit_topics.back().emplace_back(new Electron_Pair_And_Molecular_Geometry{gen, 4});
	// unit_topics.emplace_back();
	// unit_topics.back().emplace_back(new Electron_Pair_And_Molecular_Geometry{gen, 5});
	// unit_topics.emplace_back();
	// unit_topics.back().emplace_back(new Electron_Pair_And_Molecular_Geometry{gen, 6});
	std::vector<std::vector<std::unique_ptr<Question>>> units;
	for (auto & unit : unit_topics) {
		units.emplace_back();
		for (auto & topic : unit) {
			for (size_t i = 0; i < min_num_correct; i++) {
				units.back().emplace_back(topic->make_copy(gen));
			}
		}
	}
	unit_topics.emplace_back();
	// unit_topics.back().emplace_back(new Pythagorean_Theorem{gen});
	// unit_topics.back().emplace_back(new Pythagorean_Identities{gen});
	unit_topics.back().emplace_back(new Radians_To_Degrees{gen});
	// unit_topics.back().emplace_back(new Simple_Trig{gen});
	// unit_topics.back().emplace_back(new Point_From_Angle_And_Other_Point{gen});
	// unit_topics.back().emplace_back(new Unit_Circle{gen, 0});
	// unit_topics.back().emplace_back(new Unit_Circle{gen, 1});
	// unit_topics.back().emplace_back(new Unit_Circle{gen, 2});
	// unit_topics.back().emplace_back(new Inverse_Unit_Circle{gen, 0});
	// unit_topics.back().emplace_back(new Inverse_Unit_Circle{gen, 1});
	// unit_topics.back().emplace_back(new Inverse_Unit_Circle{gen, 2});
	// unit_topics.back().emplace_back(new Sine_Cosine_Range_Amplitude_Midline{gen});
	units.emplace_back();
	std::queue<std::unique_ptr<Question>> extra_review_questions;
	std::string user_answer;
	std::unique_ptr<Question> cur_question;
	size_t num_units_to_review = 0;
	for (auto& unit : units) {
		size_t total_number_of_questions_in_unit_answered = 0;
		for (size_t i = 0; (i < (extra_review_questions.size() + 2) / 2) && !extra_review_questions.empty(); i++) {
			unit.emplace_back(std::move(extra_review_questions.front()));
			extra_review_questions.pop();
		}
		for (size_t cur_unit = 0; cur_unit < num_units_to_review; cur_unit++) {
			for (auto& cur_topic : unit_topics.at(cur_unit)) {
				unit.emplace_back(cur_topic->make_copy(gen));
			}
		}
		std::shuffle(unit.begin(), unit.end(), gen);
		while (!unit.empty()) {
			std::uniform_int_distribution<size_t> question_index{(size_t)0, unit.size() - 1};
			size_t index = question_index(gen);
			std::unique_ptr<Question>& cur_question = unit.at(index);
			std::cout << "========================================\n";
			std::cout << cur_question->get_question() << "\n";
			// std::cout << cur_question->get_explanation() << "\n";
			std::getline(std::cin, user_answer);
			std::string explanation = cur_question->get_explanation();
			if (cur_question->check_answer(user_answer)) {
				cur_question->add_correct();
				std::iter_swap(unit.end() - 1, unit.begin() + index);
				unit.pop_back();
				std::cout << "\t========================================\n";
				std::cout << "\t============    Correct!    ============\n";
				std::cout << "\t========================================\n";
				std::cout << "\tOnly " << unit.size() << " more questions to go.\n";
				total_number_of_questions_in_unit_answered++;
				total_number_of_questions_answered++;
			} else {
				cur_question->add_incorrect();
				unit.emplace_back(std::move(cur_question->make_copy(gen)));
				extra_review_questions.emplace(std::move(cur_question->make_copy(gen)));
				std::cout << "\t========================================\n";
				std::cout << "\t============   Incorrect!    ===========\n";
				std::cout << "\t========================================\n";
				std::cout << "\tWe've added a question of this type, so you now have " << unit.size() << " more questions left.\n";
			}
			std::cout << "\tExplanation: " << explanation;
			std::cout << "\n\n";
		}
		std::cout << "========================================\n";
		std::cout << "========================================\n";
		std::cout << "You answered " << total_number_of_questions_in_unit_answered << " questions in this unit.\n";
		std::cout << "========================================\n";
		num_units_to_review++;
	}
	std::cout << "========================================\n";
	std::cout << "========================================\n";
	std::cout << "You answered " << total_number_of_questions_answered << " questions total.\n";
	size_t unit_index = 1;
	for (const auto& unit : unit_topics) {
		std::cout << "Unit " << unit_index << "\n";
		for (const auto& topic : unit) {
			std::cout << "\tTopic: " << topic->get_topic_name() << "\n";
			std::cout << "\tNum Correct: " << topic->num_correct() << "\tNum Incorrect: " << topic->num_incorrect() << "\tNum Worked: " << topic->num_worked() << "\n";
			std::cout << "\tEstimated Accuracy: " << (double)(topic->num_correct()) / ((double)(topic->num_worked()) + 1.0) << "\n";
		}
		unit_index++;
	}
	std::cout << "========================================\n";
	std::cout << "========================================\n";
}
