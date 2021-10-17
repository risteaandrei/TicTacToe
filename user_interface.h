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

	void SetAIThinking(bool is_thinking) { ai_thinking_ = is_thinking; }
private:
	char Convert(CellValue v) const;
	const std::string& TranslateColor(Color color) const;

	const std::string color_none_ = "\033[0;37m";
	const std::string color_red_ = "\033[0;31m";
	const std::string color_green_ = "\033[0;32m";
	const std::string color_blue_ = "\033[0;34m";

	const std::string menu_help_ = "Use UP/DOWN arrows to navigate, ENTER to select.";
	const std::string in_game_help_ = "Use UP/DOWN/LEFT/RIGHT arrows to navigate, SPACE to select, ESC to open in-game menu.";

	std::string text_color_;
	std::string x_color_;
	std::string o_color_;

	PlayerSide side_;

	bool ai_thinking_ = false;
};

