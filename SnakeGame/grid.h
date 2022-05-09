#ifndef GRID_H
#define GRID_H
#include <utility>

using namespace std;

constexpr int GRID_WIDTH = 40;
constexpr int GRID_HEIGHT = 40;

enum gridContents{
	EMPTY,
	SNAKE,
	FOOD
};

enum class directions{
	UP,
	DOWN,
	RIGHT,
	LEFT
};

class grid{
public:
	gridContents a[GRID_HEIGHT][GRID_WIDTH];
	
	// Member Functions
	grid();	// Constructor
	void reset();
	gridContents getContents(std::pair<int, int> coords) const;
	void new_food();
};

#endif // GRID_H