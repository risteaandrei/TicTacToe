#include "ai.h"

#include <ctime>
#include <limits>
#include <vector>

// Minimax implementation for TicTacToe
// https://www.freecodecamp.org/news/how-to-make-your-tic-tac-toe-game-unbeatable-by-using-the-minimax-algorithm-9d690bad4b37/
Move AI::Minimax(Board& board, PlayerType player, unsigned depth) {
	const auto free_cells = board.GetFreeCells();

	if (board.GetWinner() == Winner::kHuman) {
		return { {}, -1 * int(depth) };
	}
	else if (board.GetWinner() == Winner::kAI) {
		return { {}, 1 * int(depth) };
	} else if (free_cells.size() == 0) {
		return { {}, 0 };
	}
	else if (--depth == 0) {
		return { {}, 0 };
	}

	std::vector<Move> moves(free_cells.size());
	size_t current_move = 0;

	for (unsigned i : free_cells) {
		Move& move = moves[current_move++];
		move.index = i;
		board.SetTurn(player);
		board.Mark(board.RawToPos(i));
		move.score = Minimax(board, 
			(player == PlayerType::kAI) ? PlayerType::kHuman : PlayerType::kAI, depth).score;
		board.ResetCell(board.RawToPos(i));
	}

	size_t best_move = 0;

	if (player == PlayerType::kAI) {
		int best_score = std::numeric_limits<int>::min();
		for (size_t i = 0; i < moves.size(); ++i) {
			if (moves[i].score > best_score) {
				best_score = moves[i].score;
				best_move = i;
			}
		}
	}
	else {
		int best_score = std::numeric_limits<int>::max();
		for (size_t i = 0; i < moves.size(); ++i) {
			if (moves[i].score < best_score) {
				best_score = moves[i].score;
				best_move = i;
			}
		}
	}

	return moves[best_move];
}

Position AI::ComputeMinimax(const Board& board, unsigned depth) {
	Board work_board = board;

	return board.RawToPos(Minimax(work_board, PlayerType::kAI, depth).index);
}

Position AI::Compute(const Board& board) {
	switch (difficulty_)
	{
	case Difficulty::kEasy:
		return ComputeMinimax(board, easy_depth_);
	case Difficulty::kMedium:
		return ComputeMinimax(board, medium_depth_);
	default: // Difficulty::kHard
		return ComputeMinimax(board, hard_depth_);
	}
}
