#include "input.h"

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

UserInput Input::GetUserInput() const {
	 int kb_code = _getch();

     // std::cout << "Pressed " << kb_code << std::endl;

     switch (kb_code)
     {
     case KB_LEFT:
         return UserInput::LEFT;

     case KB_RIGHT:
         return UserInput::RIGHT;

     case KB_UP:
         return UserInput::UP;

     case KB_DOWN:
         return UserInput::DOWN;

     case KB_SPACE:
         return UserInput::SPACE;

     case KB_ESCAPE:
         return UserInput::ESCAPE;

     case KB_ENTER:
         return UserInput::ENTER;

     default:
         return UserInput::NONE;
     }
}
