#include "board.h"

#include "utils.h"

void Board::MoveLeft() {
	if (current_position_.column > 0) {
		--current_position_.column;
	}
}

void Board::MoveRight() {
	if (current_position_.column < width_ - 1) {
		++current_position_.column;
	}
}

void Board::MoveUp() {
	if (current_position_.line > 0) {
		--current_position_.line;
	}
}

void Board::MoveDown() {
	if (current_position_.line < height_ - 1) {
		++current_position_.line;
	}
}


bool Board::Mark(const Position& position) {
	CellValue& current = cells_[position.line][position.column];
	if (current != CellValue::kNone) {
		return false;
	}
	current_position_ = position;
	switch (turn_)
	{
	case PlayerType::kHuman:
		cells_[position.line][position.column] = CellValue::kHuman;
		break;
	default: // PlayerType::kAI:
		cells_[position.line][position.column] = CellValue::kAI;
		break;
	}
	//free_cells_.erase(PosToRaw(position));
	--nb_free_cells_;

	CheckWinner(winning_neighbours_);
	return true;
}

bool Board::CheckWinnerColumn(unsigned nb_neighbours) {
	const Position& p = current_position_;
	CellValue c = cells_[p.line][p.column];

	unsigned n = 1;
	unsigned index = p.line;
	while (index > 0) {
		if (cells_[--index][p.column] == c) {
			++n;
		}
		else {
			break;
		}
	}
	index = p.line;
	while (index < height_ - 1) {
		if (cells_[++index][p.column] == c) {
			++n;
		}
		else {
			break;
		}
	}
	return (n == nb_neighbours);
}

bool Board::CheckWinnerLine(unsigned nb_neighbours) {
	const Position& p = current_position_;
	CellValue c = cells_[p.line][p.column];

	unsigned n = 1;
	unsigned index = p.column;
	while (index > 0) {
		if (cells_[p.line][--index] == c) {
			++n;
		}
		else {
			break;
		}
	}
	index = p.column;
	while (index < width_ - 1) {
		if (cells_[p.line][++index] == c) {
			++n;
		}
		else {
			break;
		}
	}
	return (n == nb_neighbours);
}

bool Board::CheckWinnerDiagonal(unsigned nb_neighbours) {
	const Position& p = current_position_;
	CellValue c = cells_[p.line][p.column];

	// Left-Up to Right-Down
	unsigned n = 1;
	Position p2 = p;
	while (p2.line > 0 && p2.column > 0) {
		if (cells_[--p2.line][--p2.column] == c) {
			++n;
		}
		else {
			break;
		}
	}
	p2 = p;
	while (p2.line < height_ - 1 && p2.column < width_ - 1) {
		if (cells_[++p2.line][++p2.column] == c) {
			++n;
		}
		else {
			break;
		}
	}
	if (n == nb_neighbours) {
		return true;
	}

	// Left-Down to Right-Up
	n = 1;
	p2 = p;
	while (p2.line > 0 && p2.column < width_ - 1) {
		if (cells_[--p2.line][++p2.column] == c) {
			++n;
		}
		else {
			break;
		}
	}
	p2 = p;
	while (p2.line < height_ - 1 && p2.column > 0) {
		if (cells_[++p2.line][--p2.column] == c) {
			++n;
		}
		else {
			break;
		}
	}

	return (n == nb_neighbours);
}

void Board::CheckWinner(unsigned nb_neighbours) {
	if (CheckWinnerColumn(nb_neighbours)
		|| CheckWinnerLine(nb_neighbours)
		|| CheckWinnerDiagonal(nb_neighbours)) {
		winner_ = (turn_ == PlayerType::kHuman)
			? Winner::kHuman
			: Winner::kAI;
	}
	else if (nb_free_cells_ == 0) {
		winner_ = Winner::kDraw;
	}
}

void Board::Reset() {
	current_position_.line = 0;
	current_position_.column = 0;
	winner_ = Winner::kNone;
	for (size_t i = 0; i < height_; ++i) {
		for (size_t j = 0; j < width_; ++j) {
			cells_[i][j] = CellValue::kNone;
			unsigned raw_pos = i * width_ + j;
			//free_cells_.insert(raw_pos);
		}
	}
	turn_ = PlayerType::kHuman;
	nb_free_cells_ = width_ * height_;
}

void Board::ResetCell(const Position& p) {
	cells_[p.line][p.column] = CellValue::kNone;
	//free_cells_.insert(PosToRaw(p));
	++nb_free_cells_;
	winner_ = Winner::kNone;
}

std::ostream& operator<< (std::ostream& out, const Position& position) {
	return out << position.column << " " << position.line << " ";
}

std::ostream& operator<< (std::ostream& out, const Cells& cells) {
	for (const auto& row: cells) {
		for (auto cell: row) {
			out << as_integer(cell) << " ";
		}
	}
	return out;
}

void Board::Save(std::ostream& f) const {
	f << height_ << " ";
	f << width_ << " ";
	f << as_integer(turn_) << " ";
	f << current_position_ << " ";
	f << cells_ << " ";
}

std::istream& operator>> (std::istream& in, Position& position) {
	in >> position.column;
	in >> position.line;

	return in;
}

std::istream& operator>> (std::istream& in, PlayerType& turn) {
	unsigned turn_u;
	in >> turn_u;
	turn = static_cast<PlayerType>(turn_u);

	return in;
}

void Board::Load(std::istream& f) {
	f >> height_;
	f >> width_;
	f >> turn_;
	f >> current_position_;

	unsigned cell_u;

	cells_.resize(height_);
	//free_cells_.clear();
	nb_free_cells_ = 0;
	for (size_t i = 0; i < height_; ++i) {
		cells_[i].resize(width_);
		for (size_t j = 0; j < width_; ++j) {
			f >> cell_u;
			cells_[i][j] = static_cast<CellValue>(cell_u);
			nb_free_cells_ += (cells_[i][j] == CellValue::kNone);
		}
	}
}

bool Board::HasMarkedNeighbors(const Position& p) const {
	if (p.line > 0) {
		if (cells_[p.line - 1][p.column] != CellValue::kNone) {
			return true;
		}
		if (p.column > 0 && cells_[p.line - 1][p.column - 1] != CellValue::kNone) {
			return true;
		}
		if (p.column < width_ - 1 && cells_[p.line - 1][p.column + 1] != CellValue::kNone) {
			return true;
		}
	}

	if (p.line < height_ - 1) {
		if (cells_[p.line + 1][p.column] != CellValue::kNone) {
			return true;
		}
		if (p.column > 0 && cells_[p.line + 1][p.column - 1] != CellValue::kNone) {
			return true;
		}
		if (p.column < width_ - 1 && cells_[p.line + 1][p.column + 1] != CellValue::kNone) {
			return true;
		}
	}

	if (p.column > 0 && cells_[p.line][p.column - 1] != CellValue::kNone) {
		return true;
	}

	if (p.column < width_ - 1 && cells_[p.line][p.column + 1] != CellValue::kNone) {
		return true;
	}

	return false;
}
