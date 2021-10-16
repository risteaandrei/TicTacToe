// TicTacToe.cpp : This file contains the 'main' function. Program execution begins and ends there.

#include "game.h"

int main() {
	srand((unsigned int)time(nullptr));

	Game c;
	c.Run();

	/* TODO
	* - difficulty config + persistent
	* - decouple Board from AI to re-use AI
	* - confirm load game from in-game menu
	* - board size config + persistent
	* - first move before game start
	*/

}
