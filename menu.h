#pragma once

#include <string>
#include <vector>

#include "utils.h"

enum class GameState;

struct MenuItem {
	std::string text;
	GameState out_state;
};

struct Menu {
	std::string title;
	std::vector<MenuItem> items;
};

enum class MenuType {
	kMain
	, kInGame
	, kRestart
	, kOverwriteSave
	, kSaveConfirmed
	, kPickASide
	, kConfirmAbort
	, kOptions
	, kColors
	, kTextColor
	, kXColor
	, kOColor
	, kDifficulty
	, kNoSavedGame
};

class Menus {
public:
	Menus();

	size_t GetSelectedItem() const { return selected_item_; }
	const std::vector<MenuItem>& GetItems() const { return menus_[as_integer(current_menu_)].items; }
	const std::string& GetTitle() const { return menus_[as_integer(current_menu_)].title; }
	const Menu& GetCurrentMenu() const { return menus_[as_integer(current_menu_)]; }
	GameState GetOutState() const { return menus_[as_integer(current_menu_)].items[selected_item_].out_state; }
	MenuType GetOriginalMenu() const { return original_menu_; }
	size_t GetNumberOfMenus() const { return menus_.size(); }

	void SetCurrentMenu(MenuType menu) {
		current_menu_ = menu;
		if (menu == MenuType::kMain || menu == MenuType::kInGame) {
			original_menu_ = menu;
		}
		selected_item_ = 0;
	}

	void SetSelectedItem(size_t item) { selected_item_ = item; }

	void MoveUp();
	void MoveDown();

private:
	size_t selected_item_ = 0;
	MenuType current_menu_ = MenuType::kMain;
	MenuType original_menu_ = MenuType::kMain;
	std::vector<Menu> menus_;
};

