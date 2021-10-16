#pragma once

enum KeyCode {
	KB_ENTER = 13
	, KB_ESCAPE = 27
	, KB_SPACE = 32
	, KB_UP = 72
	, KB_LEFT = 75
	, KB_RIGHT = 77
	, KB_DOWN = 80
};

enum class UserInput {
	UP
	, DOWN
	, LEFT
	, RIGHT
	, SPACE
	, ENTER
	, ESCAPE
	, NONE
};

class Input
{
public:
	UserInput GetUserInput() const;
};

