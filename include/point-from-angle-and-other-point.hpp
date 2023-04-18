#pragma once
#include"question.hpp"

class Point_From_Angle_And_Other_Point : public Question {
QUESTION_STANDARD_DECL(Point_From_Angle_And_Other_Point)
public:
	Point_From_Angle_And_Other_Point(std::mt19937& gen);
private:
	double answer;
	std::uniform_int_distribution<int> val_chooser{-200, 200};
	std::uniform_int_distribution<size_t> coord_chooser{0, 1};
};
