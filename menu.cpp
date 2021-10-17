#include "menu.h"

#include "game.h"

void Menus::MoveUp() {
    if (selected_item_ > 0) {
        --selected_item_;
    }
    else {
        selected_item_ = menus_[as_integer(current_menu_)].items.size() - 1;
    }
}

void Menus::MoveDown() {
    if (selected_item_ < menus_[as_integer(current_menu_)].items.size() - 1) {
        ++selected_item_;
    }
    else {
        selected_item_ = 0;
    }
}

Menus::Menus()
	: menus_({
		{
			{ "Main Menu" },
			{
				{ "New Game", GameState::kSidePickMenu }
			  , { "Load Game", GameState::kLoad }
			  , { "Options", GameState::kOptionsMenu }
			  , { "Exit", GameState::kExit }
			}
	  	}
	  , {
			{ "Menu" },
			{
				{ "Restart game", GameState::kRestartMenu }
			  , { "Save game", GameState::kCheckExistingSavedGame }
			  , { "Load game", GameState::kLoad }
			  , { "Options", GameState::kOptionsMenu }
			  , { "Exit to main menu", GameState::kExitToMainMenu }
			  , { "Return to game", GameState::kPlaying }
			}
		}
	  , {
			{ "Are you sure you want to restart?" },
			{
				{ "Yes", GameState::kRestart }
			  , { "No", GameState::kInGameMenu }
			}
	    }
	  , {
			{ "Are you sure you want to overwrite previously saved game?" },
			{
				{ "Yes", GameState::kSaveOverwrite }
			  , { "No", GameState::kInGameMenu }
			}
		}
	  , {
			{ "Game saved successfully" },
			{
				{ "OK", GameState::kInGameMenu }
			}
		}
	  , {
			{ "Pick a side" },
			{
				{ "X", GameState::kSetSide }
			  , { "0", GameState::kSetSide }
			}
		}
	  , {
			{ "Are you sure you want to abort current game?" },
			{
				{ "Yes", GameState::kAbort }
			  , { "No", GameState::kInGameMenu }
			}
		}
	  , {
			{ "Options" },
			{
				{ "Difficulty", GameState::kDifficultyMenu }
			  , { "Colors", GameState::kColorsMenu }
			  , { "Return to previous menu", GameState::kOriginalMenu }
			}
		}
	  , {
			{ "Colors" },
			{
				{ "Menu color", GameState::kTextColorMenu }
			  , { "X color", GameState::kXColorMenu }
			  , { "0 color", GameState::kOColorMenu }
			  , { "Return to previous menu", GameState::kOptionsMenu }
			}
		}
	  , {
			{ "Menu color" },
			{
				{ "None", GameState::kSetTextColor }
			  ,	{ "Red", GameState::kSetTextColor }
			  , { "Green", GameState::kSetTextColor }
			  , { "Blue", GameState::kSetTextColor }
			}
		}
	  , {
			{ "X color" },
			{
				{ "None", GameState::kSetXColor }
			  ,	{ "Red", GameState::kSetXColor }
			  , { "Green", GameState::kSetXColor }
			  , { "Blue", GameState::kSetXColor }
			}
		}
	  , {
			{ "0 color" },
			{
				{ "None", GameState::kSetOColor }
			  ,	{ "Red", GameState::kSetOColor }
			  , { "Green", GameState::kSetOColor }
			  , { "Blue", GameState::kSetOColor }
			}
		}
	  , {
			{ "Difficulty" },
			{
				{ "Easy", GameState::kSetDifficulty }
			  ,	{ "Medium", GameState::kSetDifficulty }
			  , { "Hard", GameState::kSetDifficulty }
			}
		}
	}) {}
