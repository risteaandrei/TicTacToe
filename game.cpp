#include "game.h"

#include <chrono>
#include <iostream>
#include <fstream>
#include <thread>

#include "board.h"

void Game::Run() {
    // Start
    LoadOptions();
    ui_.UpdateColors(options_);
    ui_.Draw(menus_.GetCurrentMenu(), menus_.GetSelectedItem());

    while (state_ != GameState::kExit)
    {
        UserInput user_input = input_.GetUserInput();

        switch (state_)
        {
        case GameState::kPlaying:
            handlePlayingEvent(user_input);
            break;
        case GameState::kGameEnd:
            handleGameEndEvent();
            break;
        default: // all menu events
            handleMenuEvent(user_input);
            break;
        }
    }
}

Game::Game()
    : state_(GameState::kMainMenu)
    , board_(board_width_, board_height_, winning_neighbours_, PlayerType::kAI)
{
    game_state_to_menu_type[GameState::kMainMenu] = MenuType::kMain;
    game_state_to_menu_type[GameState::kInGameMenu] = MenuType::kInGame;
    game_state_to_menu_type[GameState::kRestartMenu] = MenuType::kRestart;
    game_state_to_menu_type[GameState::kConfirmOverwriteMenu] = MenuType::kOverwriteSave;
    game_state_to_menu_type[GameState::kSaveConfirmedMenu] = MenuType::kSaveConfirmed;
    game_state_to_menu_type[GameState::kSaveOverwrite] = MenuType::kSaveConfirmed;
    game_state_to_menu_type[GameState::kSidePickMenu] = MenuType::kPickASide;
    game_state_to_menu_type[GameState::kExitToMainMenu] = MenuType::kConfirmAbort;
    game_state_to_menu_type[GameState::kOptionsMenu] = MenuType::kOptions;
    game_state_to_menu_type[GameState::kColorsMenu] = MenuType::kColors;
    game_state_to_menu_type[GameState::kTextColorMenu] = MenuType::kTextColor;
    game_state_to_menu_type[GameState::kXColorMenu] = MenuType::kXColor;
    game_state_to_menu_type[GameState::kOColorMenu] = MenuType::kOColor;
    game_state_to_menu_type[GameState::kDifficultyMenu] = MenuType::kDifficulty;
    game_state_to_menu_type[GameState::kNoSavedGameMenu] = MenuType::kNoSavedGame;
}

void Game::SaveGame() const {
    std::ofstream f(save_file_);
    board_.Save(f);
}

void Game::LoadGame() {
    std::ifstream f(save_file_);
    board_.Load(f);
}

void Game::SaveOptions() const {
    std::ofstream f(options_file_);
    f << options_;
}

void Game::LoadOptions() {
    std::ifstream f(options_file_);
    if (f.good()) {
        f >> options_;
    }
}

void Game::EndGame() {
    state_ = GameState::kGameEnd;
}

void Game::handlePlayingEvent(UserInput user_input) {
    switch (user_input)
    {
    case UserInput::LEFT:
        board_.MoveLeft();
        ui_.Draw(board_);
        break;

    case UserInput::RIGHT:
        board_.MoveRight();
        ui_.Draw(board_);
        break;

    case UserInput::UP:
        board_.MoveUp();
        ui_.Draw(board_);
        break;

    case UserInput::DOWN:
        board_.MoveDown();
        ui_.Draw(board_);
        break;

    case UserInput::SPACE:
        if (board_.Mark(board_.GetCurrentPosition())) {
            handlePlayerMove();
        }
        break;

    case UserInput::ESCAPE:
        state_ = GameState::kInGameMenu;
        menus_.SetCurrentMenu(MenuType::kInGame);
        ui_.Draw(menus_.GetCurrentMenu(), menus_.GetSelectedItem());
        break;

    }
}

void Game::handleMenuEvent(UserInput user_input) {
    switch (user_input)
    {
    case UserInput::UP:
        menus_.MoveUp();
        ui_.Draw(menus_.GetCurrentMenu(), menus_.GetSelectedItem());
        break;

    case UserInput::DOWN:
        menus_.MoveDown();
        ui_.Draw(menus_.GetCurrentMenu(), menus_.GetSelectedItem());
        break;

    case UserInput::ENTER:
        state_ = menus_.GetOutState();
        switch (state_)
        {
        case GameState::kRestart:
            handleRestart();
            break;
        case GameState::kCheckExistingSavedGame:
            handleSave();
            break;
        case GameState::kSaveOverwrite:
            SaveGame();
            break;
        case GameState::kLoad:
            handleLoad();
            break;
        case GameState::kSetSide:
            handleSidePick();
            break;
        case GameState::kAbort:
            handleAbort();
            break;
        case GameState::kSetTextColor:
        case GameState::kSetXColor:
        case GameState::kSetOColor:
            handleColor();
            break;
        case GameState::kExit:
            handleExit();
            break;
        case GameState::kSetDifficulty:
            handleDifficulty();
            break;
        default:
            break;
        }

        if (state_ == GameState::kOriginalMenu) {
            menus_.SetCurrentMenu(menus_.GetOriginalMenu());
        }
        else {
            menus_.SetCurrentMenu(game_state_to_menu_type[state_]);
        }

        SetSelectedItem();

        if (state_ == GameState::kPlaying) {
            ui_.Draw(board_);
        }
        else {
            ui_.Draw(menus_.GetCurrentMenu(), menus_.GetSelectedItem());
        }
        break;
    }
}

void Game::handleGameEndEvent() {
    board_.Reset();
    state_ = GameState::kMainMenu;
    menus_.SetCurrentMenu(MenuType::kMain);
    ui_.Draw(menus_.GetCurrentMenu(), menus_.GetSelectedItem());
}

void Game::handleRestart() {
    board_.Reset();
    state_ = GameState::kPlaying;
}

void Game::handleSave() {
    std::ifstream file(save_file_);
    if (file.good()) {
        state_ = GameState::kConfirmOverwriteMenu;
    }
    else {
        SaveGame();
        state_ = GameState::kSaveConfirmedMenu;
    }
}

void Game::handleLoad() {
    std::ifstream file(save_file_);
    if (file.good()) {
        LoadGame();
        state_ = GameState::kPlaying;
    }
    else {
        state_ = GameState::kNoSavedGameMenu;
    }
}

void Game::handleSidePick() {
    ui_.SetSide(menus_.GetSelectedItem() ? PlayerSide::O : PlayerSide::X);
    state_ = GameState::kPlaying;
}

void Game::handleAbort() {
    board_.Reset();
    state_ = GameState::kMainMenu;
}

void Game::handleColor() {
    Color color = static_cast<Color>(menus_.GetSelectedItem());
    if (state_ == GameState::kSetTextColor) {
        options_.text_color = color;
    }
    else if (state_ == GameState::kSetXColor) {
        options_.x_color = color;
    }
    else if (state_ == GameState::kSetOColor) {
        options_.o_color = color;
    }
    state_ = GameState::kOptionsMenu;
    ui_.UpdateColors(options_);
    ui_.Draw(menus_.GetCurrentMenu(), menus_.GetSelectedItem());
}

void Game::handleDifficulty() {
    options_.difficulty = static_cast<Difficulty>(menus_.GetSelectedItem());
    state_ = GameState::kOptionsMenu;
}

void Game::handleExit() {
    SaveOptions();
}

void Game::handlePlayerMove() {
    if (board_.GetNbFreeCells() > 25 / (static_cast<unsigned>(options_.difficulty) + 1)) {
        ui_.SetAIThinking(true);
    }
    ui_.Draw(board_);

    if (board_.GetWinner() != Winner::kNone) {
        EndGame();
    }
    else {
        board_.SetTurn(PlayerType::kAI);

        Position ai_pos = ai_.Compute(board_, options_.difficulty);
        board_.Mark(ai_pos);
        ui_.SetAIThinking(false);
        ui_.Draw(board_);
        if (board_.GetWinner() != Winner::kNone) {
            EndGame();
        }

        board_.SetTurn(PlayerType::kHuman);
    }
}

void Game::SetSelectedItem() {
    switch (state_)
    {
    case GameState::kTextColorMenu:
        menus_.SetSelectedItem(as_integer(options_.text_color));
        break;
    case GameState::kXColorMenu:
        menus_.SetSelectedItem(as_integer(options_.x_color));
        break;
    case GameState::kOColorMenu:
        menus_.SetSelectedItem(as_integer(options_.o_color));
        break;
    case GameState::kDifficultyMenu:
        menus_.SetSelectedItem(as_integer(options_.difficulty));
        break;
    default:
        break;
    }
}
