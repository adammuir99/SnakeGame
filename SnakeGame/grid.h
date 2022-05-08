#ifndef GRID_H
#define GRID_H

constexpr int GRID_WIDTH = 50;
constexpr int GRID_HEIGHT = 50;

enum gridContents{
	EMPTY,
	HEAD,
	BODY,
	TAIL,
	FOOD
};

class grid{
public:
	int a[GRID_HEIGHT][GRID_WIDTH];
	
	void new_food();
	void reset();
};

#endif // GRID_H