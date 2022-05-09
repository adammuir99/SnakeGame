#ifndef SNAKE_H
#define SNAKE_H

#include <list>

class snake{
public:
	std::list<std::pair<int, int>> snakeList;
	int snakeLength;

	// Member Functions
	snake();	// Constructor
	std::pair<int, int> getHead() const;
};

#endif // SNAKE_H