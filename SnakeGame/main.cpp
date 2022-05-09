#include "SDL.h"
#include "grid.h"
#include "snake.h"
using namespace std;

bool check_valid(grid& theGrid, snake& theSnake, directions direction) {
	pair<int, int> head = theSnake.getHead();
	pair<int, int> next_move;
	
	// Check if the snake moves into the border or into itself
	switch (direction) {
		case directions::UP:
			if (get<0>(head) == 0) {
				return false;
			}
			next_move = make_pair(get<0>(head) - 1, get<1>(head));
			if (theGrid.getContents(next_move) == SNAKE) {
				return false;
			}
			break;
		case directions::DOWN:
			if (get<0>(head) == GRID_HEIGHT - 1) {
				return false;
			}
			next_move = make_pair(get<0>(head) + 1, get<1>(head));
			if (theGrid.getContents(next_move) == SNAKE) {
				return false;
			}
			break;
		case directions::LEFT:
			if (get<1>(head) == 0) {
				return false;
			}
			next_move = make_pair(get<0>(head), get<1>(head) - 1);
			if (theGrid.getContents(next_move) == SNAKE) {
				return false;
			}
			break;
		case directions::RIGHT:
			if (get<1>(head) == GRID_WIDTH - 1) {
				return false;
			}
			next_move = make_pair(get<0>(head), get<1>(head) + 1);
			if (theGrid.getContents(next_move) == SNAKE) {
				return false;
			}
			break;
	}

	return true;
}

void make_move(grid& theGrid, snake& theSnake, directions direction) {
	pair<int, int> head = theSnake.getHead();
	pair<int, int> next_move;
	switch (direction) {
		case(directions::UP):
			next_move = make_pair(get<0>(head) - 1, get<1>(head));
			break;
		case(directions::DOWN):
			next_move = make_pair(get<0>(head) + 1, get<1>(head));
			break;
		case(directions::LEFT):
			next_move = make_pair(get<0>(head), get<1>(head) - 1);
			break;
		case(directions::RIGHT):
			next_move = make_pair(get<0>(head), get<1>(head) + 1);
			break;
	}
	// Check if we're moving into food in which the snake will have to grow
	if (theGrid.a[next_move.second][next_move.first] == FOOD) {
		theSnake.add_head(next_move);
		theGrid.place_snake(theSnake);
		theGrid.new_food();
	}
	else {
		theSnake.add_head(next_move);
		theSnake.remove_tail();
		theGrid.place_snake(theSnake);
	}
	return;
}

int main(int argc, char *argv[]) {

	// Create the SDL window and renderer
	SDL_Init(SDL_INIT_EVERYTHING);
	SDL_Window *window = SDL_CreateWindow("Snake", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_SHOWN);
	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);

	// Create snake and grid objects
	grid theGrid;
	snake theSnake;
	
	// Randomize the starting direction
	directions newDirection = directions(rand()%4);

	bool isRunning = true;	// Flag controls graphics
	bool gameActive = true;	// Flag controls game
	// Main Application Loop
	while (isRunning) {
		SDL_Event event;
		
		// (1) Handle Input
		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT) {
				isRunning = false;
			}
		}

		// (2) Handle Updates
		if (gameActive) {
			if (check_valid(theGrid, theSnake, newDirection)) {
				make_move(theGrid, theSnake, newDirection);
			}
			else {
				gameActive = false;
			}
		}
		// (3) Clear and Draw the Screen
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);	// Black
		SDL_RenderClear(renderer);

		SDL_SetRenderDrawColor(renderer, 233, 233, 233, 255);	// Grey
		// Create Rectangle
		SDL_Rect rect;
		rect.x = 0;
		rect.y = 0;
		rect.w = 200;
		rect.h = 600;
		SDL_RenderFillRect(renderer, &rect);
		SDL_RenderPresent(renderer);
	}

	return 0;
}