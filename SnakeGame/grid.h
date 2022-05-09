#ifndef GRID_H
#define GRID_H
#include <utility>
#include "snake.h"

using namespace std;

constexpr int GRID_WIDTH = 40;
constexpr int GRID_HEIGHT = 40;

enum gridContents{
	EMPTY,
	SNAKE,
	FOOD
};

class grid{
public:
	gridContents a[GRID_HEIGHT][GRID_WIDTH];
	
	// Member Functions
	grid();	// Constructor
	void reset();
	gridContents getContents(std::pair<int, int> coords) const;
	void new_food();
	void place_snake(const snake& currSnake);
};

#endif // GRID_H