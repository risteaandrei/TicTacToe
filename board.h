#pragma once

#include <fstream>
#include <vector>

enum class CellValue {
    kNone,
    kHuman,
    kAI
};

using Cells = std::vector<std::vector<CellValue>>;

enum class Winner {
    kNone,
    kHuman,
    kAI
};

enum class PlayerType {
    kHuman,
    kAI
};

struct Position {
    unsigned line;
    unsigned column;
};

class Board {
public:
    Board(unsigned width, unsigned height, PlayerType start)
        : width_(width)
        , height_(height)
        , turn_(start)
        , current_position_{ 0, 0 }
        , winner_(Winner::kNone)
        , cells_(height_, std::vector<CellValue>(width_, CellValue::kNone)) {}

    unsigned GetWidth() const { return width_; }
    unsigned GetHeight() const { return height_; }
    CellValue GetCellValue(const Position& p) const { return cells_[p.line][p.column]; }
    const Position& GetCurrentPosition() const { return current_position_; }
    Winner GetWinner() const { return winner_; }

    void MoveLeft();
    void MoveRight();
    void MoveUp();
    void MoveDown();

    void Mark();

    void Reset();

    void Save(std::ostream& f) const;
    void Load(std::istream& f);

private:
    void CheckWinner(unsigned nb_neighbours);

    unsigned width_;
    unsigned height_;
    PlayerType turn_;
    Position current_position_;
    Winner winner_;
    Cells cells_;
};
