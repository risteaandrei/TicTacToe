#pragma once

#include "board.h"

#include <cstdlib>

#include "options.h"

struct Move {
	unsigned index = 0;
	int score = 0;
};

class AI
{
public:
	Position Compute(const Board& b, Difficulty difficulty);

private:
	Position ComputeMinimax(const Board& b, unsigned depth);
	Move Minimax(Board& board, PlayerType player, unsigned depth);

	const unsigned easy_depth_ = 2;
	const unsigned medium_depth_ = 3;
	const unsigned hard_depth_ = 10;
};
