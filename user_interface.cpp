#include "user_interface.h"

#include <iostream>

#include "game.h"

UserInterface::UserInterface()
	: text_color_(color_none_)
	, x_color_(color_none_)
	, o_color_(color_none_)
	, side_(PlayerSide::X)
{}

char UserInterface::Convert(CellValue v) const {
	switch (v)
	{
	case CellValue::kHuman:
		if (side_ == PlayerSide::X) {
			return 'X';
		}
		return '0';
	case CellValue::kAI:
		if (side_ == PlayerSide::X) {
			return '0';
		}
		return 'X';
	default:
		return ' ';
	}
}

void UserInterface::Draw(const Board& board) const {
	std::cout << color_none_;
	static const std::string sep = "-------------";

	system("CLS");
	std::cout << sep << std::endl;
	for (size_t i = 0; i < board.GetHeight(); ++i) {
		std::cout << "| ";
		for (size_t j = 0; j < board.GetWidth(); ++j) {
			char c = Convert(board.GetCellValue({ i, j }));
			if (c == '0') {
				std::cout << o_color_;
			} else if (c == 'X') {
				std::cout << x_color_;
			}
			std::cout << c << color_none_ << " | ";
		}
		std::cout << std::endl;

		if (i == board.GetCurrentPosition().line) {
			size_t j;
			for (j = 0; j < board.GetCurrentPosition().column; ++j) {
				std::cout << "----";
			}
			std::cout << "--^-";
			++j;
			for (; j < board.GetWidth(); ++j) {
				std::cout << "----";
			}
			std::cout << "-" << std::endl;
		} else {
			std::cout << sep << std::endl;
		}
	}

	if (board.GetWinner() != Winner::kNone) {
		std::cout << "Winner: " << as_integer(board.GetWinner()) << std::endl;
	}
}

void UserInterface::Draw(const Menu& menu, size_t selected_item) const {
	system("CLS");
	std::cout << text_color_;
	std::cout << menu.title << std::endl;
	for (size_t i = 0; i < menu.items.size(); ++i) {
		if (i == selected_item) {
			std::cout << "* " << menu.items[i].text << std::endl;
		}
		else {
			std::cout << "  " << menu.items[i].text << std::endl;
		}
	}
	std::cout << color_none_;
}

const std::string& UserInterface::TranslateColor(Color color) const {
	switch (color)
	{
	case Color::kNone:
		return color_none_;
	case Color::kRed:
		return color_red_;
	case Color::kGreen:
		return color_green_;
	case Color::kBlue:
		return color_blue_;
	default:
		return color_none_;
	}
}

void UserInterface::UpdateColors(const Options& options) {
	text_color_ = TranslateColor(options.text_color);
	x_color_ = TranslateColor(options.x_color);
	o_color_ = TranslateColor(options.o_color);
}
