#include "point-from-angle-and-other-point.hpp"
#include <cmath>
#include <iostream>
#include <sstream>
#include <iomanip>

Point_From_Angle_And_Other_Point::Point_From_Angle_And_Other_Point(
	std::mt19937& gen
) {
	change_vals(gen);
}

bool Point_From_Angle_And_Other_Point::check_answer(const std::string& user_ans) {
	double user_num_ans;
	try {
		user_num_ans = std::stod(user_ans);
	} catch(std::invalid_argument e) {
		return false;
	}
	return (std::abs(user_num_ans - answer) <= 0.1);
}

void Point_From_Angle_And_Other_Point::change_vals(std::mt19937& gen) {
	double p0x = val_chooser(gen);
	double p0y = val_chooser(gen);
	double p1x = val_chooser(gen);
	double p1y = val_chooser(gen);
	while (p1x == p0x) {
		p1x = val_chooser(gen);
	}
	std::stringstream strstr;
	size_t coord_to_find = coord_chooser(gen);
	strstr << std::fixed << std::setprecision(2);
	strstr << "| Points, Lines, and Slopes |: A line passes through the points\n(" << p0x << ", " << p0y << ") and (";
	explanation = "You should have calculated\n\t";
	switch (coord_to_find) {
	case 0:
		answer = p1x;
		strstr << "k, " << p1y << ")";
		explanation += "(y2 - y1) / tan(θ) + x1.";
		break;
	case 1:
		answer = p1y;
		strstr << p1x << ", k)";
		explanation += "(x2 - x1) * tan(θ) + y1.";
		break;
	}
	strstr.unsetf(std::ios_base::floatfield);
	strstr << "\nand forms an angle " << std::setprecision(7) << 180.0 * atan((p1y - p0y) / (p1x - p0x)) / M_PI << "° with the x-axis. Solve for k.";
	question = strstr.str();
	explanation += "\n\tAnswer: ";
	explanation += std::to_string(answer);
}

Question* Point_From_Angle_And_Other_Point::make_copy(std::mt19937& gen) {
	return new Point_From_Angle_And_Other_Point{gen};
}

QUESTION_STANDARD_DEFN(Point_From_Angle_And_Other_Point)
