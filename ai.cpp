#include "ai.h"

#include <ctime>
#include <limits>
#include <vector>

// Minimax implementation for TicTacToe
// https://www.freecodecamp.org/news/how-to-make-your-tic-tac-toe-game-unbeatable-by-using-the-minimax-algorithm-9d690bad4b37/
Move AI::Minimax(Board& board, PlayerType player, unsigned depth) {
	Winner winner = board.GetWinner();

	switch (winner)
	{
	case Winner::kHuman:
		return { {}, -1 * int(depth) };
	case Winner::kAI:
		return { {}, 1 * int(depth) };
	case Winner::kDraw:
		return { {}, 0 };
	default:
		break;
	}

	if (--depth == 0) {
		return { {}, 0 };
	}

	std::vector<Move> moves;
	moves.reserve(board.GetNbFreeCells());

	unsigned height = board.GetHeight();
	unsigned width  = board.GetWidth();

	for (size_t i = 0; i < height; ++i) {
		for (size_t j = 0; j < width; ++j) {
			Position p = { i, j };
			if (board.GetCellValue(p) == CellValue::kNone) {
				// Reduce number of iterations by only checking cells with marked neighbours
				// but make sure we add at least one move
				unsigned raw_pos = board.PosToRaw(p);
				if (moves.size() == 0 || board.HasMarkedNeighbors(p)) {
					moves.push_back({ raw_pos, 0});
				}
			}
		}
	}

	moves.shrink_to_fit();

	for (Move& move : moves) {
		Position p = board.RawToPos(move.index);

		board.SetTurn(player);
		board.Mark(p);
		int score = Minimax(board, 
			(player == PlayerType::kAI) ? PlayerType::kHuman : PlayerType::kAI, depth).score;
		board.ResetCell(p);

		move.score = score;
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

Position AI::Compute(const Board& board, Difficulty difficulty) {
	switch (difficulty)
	{
	case Difficulty::kEasy:
		return ComputeMinimax(board, easy_depth_);
	case Difficulty::kMedium:
		return ComputeMinimax(board, medium_depth_);
	default: // Difficulty::kHard
		return ComputeMinimax(board, hard_depth_);
	}
}
