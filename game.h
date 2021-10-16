#pragma once

#include "board.h"

#include <unordered_map>

#include "input.h"
#include "menu.h"
#include "options.h"
#include "user_interface.h"

enum class GameState {
	kPlaying
	, kMainMenu
	, kOriginalMenu
	, kInGameMenu
	, kRestartMenu
	, kRestart
	, kCheckExistingSavedGame
	, kConfirmOverwriteMenu
	, kSaveOverwrite
	, kLoad
	, kSidePickMenu
	, kSetSide
	, kExitToMainMenu
	, kOptionsMenu
	, kColorsMenu
	, kTextColorMenu
	, kXColorMenu
	, kOColorMenu
	, kSetTextColor
	, kSetXColor
	, kSetOColor
	, kExit
};

enum class PlayerSide {
	X,
	O
};

class Game {
public:
	Game();
	void Run();
private:
	GameState state_;
	UserInterface ui_;
	Input input_;
	Board board_;
	Menus menus_;
	Options options_;

	const std::string save_file_ = "game.save";
	const std::string options_file_ = "game.options";

	std::unordered_map<GameState, MenuType> game_state_to_menu_type;

	void handlePlayingEvent(UserInput user_input);
	void handleMenuEvent(UserInput user_input);
	
	void handleRestart();
	void handleSave();
	void handleLoad();
	void handleSidePick();
	void handleAbort();
	void handleColor();
	void handleExit();

	void SaveGame() const;
	void LoadGame();
	void SaveOptions() const;
	void LoadOptions();
};
