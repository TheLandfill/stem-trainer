#include "all-questions.hpp"
#include <random>
#include <iostream>
#include <vector>
#include <memory>
#include <algorithm>
#include <queue>
#include <sstream>

#ifdef WIN32
#include <windows.h>
#define SETUP_ANSI_TERMINAL setup_ansi_terminal();
void setup_ansi_terminal() {
	DWORD l_mode;
	HANDLE hstd = GetStdHandle(STD_OUTPUT_HANDLE);
	if (hstd == INVALID_HANDLE_VALUE) {
		return;
	}
	GetConsoleMode(hstd, &l_mode);
	SetConsoleMode(hstd, l_mode | DISABLE_NEWLINE_AUTO_RETURN | ENABLE_VIRTUAL_TERMINAL_PROCESSING);
}

#include <io.h>
#include <fcntl.h>

#define SETUP_UTF_8_TERMINAL \
_setmode(_fileno(stdout), _O_U8TEXT);\
_setmode(_fileno(stderr), _O_U8TEXT);
#else
#define SETUP_ANSI_TERMINAL
#define SETUP_UTF_8_TERMINAL
#endif

#ifdef WIN32
static void identify_windows_error() {
	LPWSTR err_str;
	DWORD last_err = GetLastError();
	switch (last_err) {
	case ERROR_INSUFFICIENT_BUFFER:
		err_str = L"INSUFFICIENT BUFFER";
		break;
	case ERROR_INVALID_FLAGS:
		err_str = L"INVALID FLAGS";
		break;
	case ERROR_INVALID_PARAMETER:
		err_str = L"INVALID PARAMETER";
		break;
	case ERROR_NO_UNICODE_TRANSLATION:
		err_str = L"NO UNICODE TRANSLATION";
		break;
	default:
		err_str = L"UNKNOWN ERROR";
	}
	fwprintf(stderr, L"ERROR:       %s\nERROR CODE: %ld", err_str, last_err);
}
#endif

bool utf_print(FILE* out, std::stringstream& strstr) {
	std::string str_full = strstr.str();
	const char * str = str_full.c_str();
	#pragma omp critical(thread_safe_printing)
	{
#ifdef WIN32
		int buff_length = MultiByteToWideChar(CP_UTF8, 0, str, -1, NULL, 0);
		if (buff_length < 0) {
			std::wstring error_message;
			fwprintf(stderr, L"%s",
L"The message that was supposed to be printed out cannot be printed for some\n"
L"reason. Contact the developers of the plugins in use.\n"
			);
			identify_windows_error();
			return false;
		}
		LPWSTR buffer;
		try {
			buffer = new WCHAR[buff_length];
		} catch (std::bad_alloc& e) {
			std::string cs(e.what());
			std::wstring ws;
			std::copy(cs.begin(), cs.end(), std::back_inserter(ws));
			fwprintf(stderr, L"%s\nException: %s\n",
				L"Could not allocate enough memory to print out the error message that was\n"
				L"supposed to be printed out.",
				ws.c_str()
			);
			identify_windows_error();
			return false;
		}
		int err_code = MultiByteToWideChar(CP_UTF8, 0, str, -1, buffer, buff_length);
		if (err_code == 0) {
			fwprintf(stderr, L"%s",
L"Unable to convert message to print to wide characters. Contact the developers\n"
L"of the plugins in use.\n"
			);
			identify_windows_error();
			return false;
		}
		fwprintf(out, L"%s", buffer);
		delete[] buffer;
#else
		fprintf(out, "%s", str);
#endif
	}
	strstr.str(std::string{});
	strstr.clear();
	return true;
}

int main() {
	SETUP_ANSI_TERMINAL
	SETUP_UTF_8_TERMINAL
	std::stringstream strstr;
	std::random_device rd;
	std::mt19937 gen{rd()};
	size_t min_num_correct = 3;
	size_t total_number_of_questions_answered = 0;
	std::vector<std::vector<std::unique_ptr<Question>>> unit_topics;
	// unit_topics.emplace_back();
	// unit_topics.back().emplace_back(new Pythagorean_Theorem{gen});
	// unit_topics.emplace_back();
	// unit_topics.back().emplace_back(new Pythagorean_Identities{gen});
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
	// Chem starts here
	// unit_topics.emplace_back();
	// unit_topics.back().emplace_back(new Change_In_Internal_Energy_Work_And_Heat{gen});
	// unit_topics.emplace_back();
	// unit_topics.back().emplace_back(new Wavelength_And_Frequency{gen});
	// unit_topics.emplace_back();
	// unit_topics.back().emplace_back(new Photon_Energy{gen});
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
	// unit_topics.emplace_back();
	// unit_topics.back().emplace_back(new Number_Of_Photons{gen});
	// unit_topics.emplace_back();
	// unit_topics.back().emplace_back(new Hydrogen_Energy_Levels{gen});
	// unit_topics.emplace_back();
	// unit_topics.back().emplace_back(new Electron_Orbital_Hybridization{gen});
	// unit_topics.emplace_back();
	// unit_topics.back().emplace_back(new Number_Of_Core_Electrons{gen});
	unit_topics.emplace_back();
	unit_topics.back().emplace_back(new Specific_Heat_Capacity{gen});
	//unit_topics.emplace_back();
	//unit_topics.back().emplace_back(new Period_And_Group_Given_EC{gen});
	//unit_topics.emplace_back();
	//unit_topics.back().emplace_back(new EC_Given_Ion{gen});
	//unit_topics.emplace_back();
	//unit_topics.back().emplace_back(new Diamagnetic_Vs_Paramagnetic{gen});
	// SKIP THIS ONE
	// unit_topics.emplace_back();
	// unit_topics.back().emplace_back(new Quantum_Number_Relationships{gen});
	std::vector<std::vector<std::unique_ptr<Question>>> units;
	for (auto & unit : unit_topics) {
		units.emplace_back();
		for (auto & topic : unit) {
			for (size_t i = 0; i < min_num_correct; i++) {
				units.back().emplace_back(topic->make_copy(gen));
			}
		}
	}
	units.emplace_back();
	std::queue<std::unique_ptr<Question>> extra_review_questions;
	std::string user_answer;
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
			if ((double)(cur_question->num_correct()) / (double)(cur_question->num_worked() + cur_question->get_fudge_factor()) >= 2.0 / 3.0 - 0.01) {
				cur_question->add_fudge_factor();
				strstr << "Question skipped because you've done well on\n" << cur_question->get_topic_name() << " questions.\n";
				utf_print(stdout, strstr);
				std::iter_swap(unit.end() - 1, unit.begin() + index);
				unit.pop_back();
				strstr << "Only " << unit.size() << " more questions to go.\n";
				utf_print(stdout, strstr);
				continue;
			}
			strstr << "========================================\n";
			strstr << cur_question->get_question() << "\n";
			utf_print(stdout, strstr);
			// std::cout << cur_question->get_explanation() << "\n";
			std::getline(std::cin, user_answer);
			std::string explanation = cur_question->get_explanation();
			if (cur_question->check_answer(user_answer)) {
				cur_question->add_correct();
				std::iter_swap(unit.end() - 1, unit.begin() + index);
				unit.pop_back();
				strstr << "\t========================================\n";
				strstr << "\t============    Correct!    ============\n";
				strstr << "\t========================================\n";
				strstr << "\tOnly " << unit.size() << " more questions to go.\n";
				total_number_of_questions_in_unit_answered++;
				total_number_of_questions_answered++;
			} else {
				cur_question->add_incorrect();
				unit.emplace_back(std::move(cur_question->make_copy(gen)));
				extra_review_questions.emplace(std::move(cur_question->make_copy(gen)));
				strstr << "\t========================================\n";
				strstr << "\t============   Incorrect!    ===========\n";
				strstr << "\t========================================\n";
				strstr << "\tWe've added a question of this type, so you now have " << unit.size() << " more questions left.\n";
			}
			strstr << "\tExplanation: " << explanation;
			strstr << "\n\n";
			utf_print(stdout, strstr);
		}
		strstr << "========================================\n";
		strstr << "========================================\n";
		strstr << "You answered " << total_number_of_questions_in_unit_answered << " questions in this unit.\n";
		strstr << "========================================\n";
		utf_print(stdout, strstr);
		num_units_to_review++;
	}
	strstr << "========================================\n";
	strstr << "========================================\n";
	strstr << "You answered " << total_number_of_questions_answered << " questions total.\n";
	utf_print(stdout, strstr);
	size_t unit_index = 1;
	for (const auto& unit : unit_topics) {
		strstr << "Unit " << unit_index << "\n";
		for (const auto& topic : unit) {
			strstr << "\tTopic: " << topic->get_topic_name() << "\n";
			strstr << "\tNum Correct: " << topic->num_correct() << "\tNum Incorrect: " << topic->num_incorrect() << "\tNum Worked: " << topic->num_worked() << "\n";
			strstr << "\tEstimated Accuracy: " << (double)(topic->num_correct()) / ((double)(topic->num_worked()) + 1.0) << "\n";
		}
		unit_index++;
	}
	strstr << "========================================\n";
	strstr << "========================================\n";
	strstr << "Hit Enter to end the program.\n";
	utf_print(stdout, strstr);
	std::cin.get();
}
