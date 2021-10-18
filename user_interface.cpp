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
	std::string sep = "-";
	for (size_t i = 0; i < board.GetWidth(); ++i) {
		sep += "----";
	}

	system("CLS");
	std::cout << in_game_help_ << std::endl << std::endl;

	std::cout << sep << std::endl;
	for (unsigned i = 0; i < board.GetHeight(); ++i) {
		std::cout << "| ";
		for (unsigned j = 0; j < board.GetWidth(); ++j) {
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

	Winner winner = board.GetWinner();
	if (winner != Winner::kNone) {
		switch (winner)
		{
		case Winner::kHuman:
			std::cout << "Congratulations, you won!" << std::endl;
			break;
		case Winner::kAI:
			std::cout << "You got beaten by AI :(" << std::endl;
			break;
		case Winner::kDraw:
			std::cout << "Draw game, nobody won." << std::endl;
			break;
		default:
			break;
		}
		std::cout << "Press any key to continue" << std::endl;
	}
	else if (ai_thinking_) {
		std::cout << "AI is thinking, please be patient..." << std::endl;
	}
}

void UserInterface::Draw(const Menu& menu, size_t selected_item) const {
	system("CLS");
	std::cout << text_color_;
	std::cout << menu_help_ << std::endl << std::endl;
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
