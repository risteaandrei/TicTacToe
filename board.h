#pragma once

#include <fstream>
#include <set>
#include <vector>

enum class CellValue {
    kNone
    , kHuman
    , kAI
};

using Cells = std::vector<std::vector<CellValue>>;

enum class Winner {
    kNone
    , kHuman
    , kAI
    , kDraw
};

enum class PlayerType {
    kHuman
    , kAI
};

struct Position {
    unsigned line;
    unsigned column;
};

class Board {
public:
    Board(unsigned width, unsigned height, unsigned winning_neighbours, PlayerType start)
        : width_(width)
        , height_(height)
        , turn_(start)
        , cells_(height_, std::vector<CellValue>(width_))
        , winning_neighbours_(winning_neighbours) {
        Reset();
    }

    unsigned GetWidth() const { return width_; }
    unsigned GetHeight() const { return height_; }
    unsigned GetSize() const { return width_ * height_; }
    CellValue GetCellValue(const Position& p) const { return cells_[p.line][p.column]; }
    const Position& GetCurrentPosition() const { return current_position_; }
    PlayerType GetTurn() const { return turn_; }
    Winner GetWinner() const { return winner_; }
    bool HasMarkedNeighbors(const Position& p) const;
    //const std::set<unsigned>& GetFreeCells() const { return free_cells_; }
    unsigned GetNbFreeCells() const { return nb_free_cells_; }
    Position RawToPos(unsigned pos) const { return { pos / width_, pos % width_ }; }
    unsigned PosToRaw(Position pos) const { return pos.line * width_ + pos.column; }

    void SetTurn(PlayerType turn) { turn_ = turn; }

    void MoveLeft();
    void MoveRight();
    void MoveUp();
    void MoveDown();

    bool Mark(const Position& p);

    void Reset();
    void ResetCell(const Position& p);

    void Save(std::ostream& f) const;
    void Load(std::istream& f);

private:
    void CheckWinner(unsigned nb_neighbours);
    bool CheckWinnerLine(unsigned nb_neighbours);
    bool CheckWinnerColumn(unsigned nb_neighbours);
    bool CheckWinnerDiagonal(unsigned nb_neighbours);

    unsigned width_;
    unsigned height_;
    PlayerType turn_;
    Position current_position_;
    Winner winner_;
    Cells cells_;
    //std::set<unsigned> free_cells_;
    unsigned nb_free_cells_;
    unsigned winning_neighbours_;
};
