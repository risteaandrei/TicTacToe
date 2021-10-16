#pragma once

#include "board.h"
#include "menu.h"
#include "options.h"

enum class PlayerSide;

class UserInterface {
public:
	UserInterface();

	void Draw(const Board& board) const;
	void Draw(const Menu& menu, size_t selected_item) const;

	void SetSide(PlayerSide side) { side_ = side; }
	void UpdateColors(const Options& options);
private:
	const std::string color_none_ = "\033[0;37m";
	const std::string color_red_ = "\033[0;31m";
	const std::string color_green_ = "\033[0;32m";
	const std::string color_blue_ = "\033[0;34m";

	std::string text_color_;
	std::string x_color_;
	std::string o_color_;

	PlayerSide side_;

	char Convert(CellValue v) const;
	const std::string& TranslateColor(Color color) const;
};

