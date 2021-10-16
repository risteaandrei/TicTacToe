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


void Board::Mark() {
	CellValue& current = cells_[current_position_.line][current_position_.column];
	if (current != CellValue::kNone) {
		return;
	}
	switch (turn_)
	{
	case PlayerType::kHuman:
		cells_[current_position_.line][current_position_.column] = CellValue::kHuman;
		turn_ = PlayerType::kAI;
		break;
	case PlayerType::kAI:
		cells_[current_position_.line][current_position_.column] = CellValue::kAI;
		turn_ = PlayerType::kHuman;
		break;
	default:
		break;
	}

	CheckWinner(3);
}

void Board::CheckWinner(unsigned nb_neighbours) {
	const Position& p = current_position_;
	CellValue c = cells_[p.line][p.column];
	// Check column
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
	if (n == nb_neighbours) {
		// Reverse winner because the turn has already changed
		winner_ = (turn_ == PlayerType::kHuman)
			? Winner::kAI
			: Winner::kHuman;
	}
}

void Board::Reset() {
	current_position_.line = 0;
	current_position_.column = 0;
	winner_ = Winner::kNone;
	for (size_t i = 0; i < height_; ++i) {
		for (size_t j = 0; j < width_; ++j) {
			cells_[i][j] = CellValue::kNone;
		}
	}
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
	for (size_t i = 0; i < height_; ++i) {
		cells_[i].resize(width_);
		for (size_t j = 0; j < height_; ++j) {
			f >> cell_u;
			cells_[i][j] = static_cast<CellValue>(cell_u);
		}
	}
}
