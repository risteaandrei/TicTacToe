#pragma once

#include <fstream>

enum class Color {
	kNone
	, kRed
	, kGreen
	, kBlue
};

struct Options {
	Color text_color = Color::kNone;
	Color x_color = Color::kNone;
	Color o_color = Color::kNone;
};

std::ostream& operator<< (std::ostream& out, const Options& options);
std::istream& operator>> (std::istream& in, Options& options);
