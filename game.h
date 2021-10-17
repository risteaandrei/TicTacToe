#pragma once

#include "board.h"

#include <unordered_map>

#include "ai.h"
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
	, kGameEnd
	, kDifficultyMenu
	, kSetDifficulty
	, kAbort
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
	void handlePlayingEvent(UserInput user_input);
	void handleMenuEvent(UserInput user_input);
	void handleGameEndEvent();
	
	void handleRestart();
	void handleSave();
	void handleLoad();
	void handleSidePick();
	void handleAbort();
	void handleColor();
	void handleDifficulty();
	void handleExit();
	void handlePlayerMove();

	void SaveGame() const;
	void LoadGame();
	void SaveOptions() const;
	void LoadOptions();

	void SetSelectedItem();

	void EndGame();

	const std::string save_file_ = "game.save";
	const std::string options_file_ = "game.options";
	const unsigned board_width_ = 3;
	const unsigned board_height_ = 3;
	const unsigned winning_neighbours_ = 3;

	GameState state_;
	UserInterface ui_;
	Input input_;
	Board board_;
	Menus menus_;
	Options options_;
	AI ai_;

	std::unordered_map<GameState, MenuType> game_state_to_menu_type;
};
