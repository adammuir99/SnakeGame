#include "SDL.h"
#include "grid.h"
#include "snake.h"
using namespace std;

enum KeyPressSurfaces
{
	KEY_PRESS_SURFACE_DEFAULT,
	KEY_PRESS_SURFACE_UP,
	KEY_PRESS_SURFACE_DOWN,
	KEY_PRESS_SURFACE_LEFT,
	KEY_PRESS_SURFACE_RIGHT,
	KEY_PRESS_SURFACE_TOTAL
};

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
	if (theGrid.a[next_move.first][next_move.second] == FOOD) {
		// Clear the board to remove the snake from last iteration
		theGrid.reset();
		// Place the new snake location and food
		theSnake.add_head(next_move);
		theGrid.place_snake(theSnake);
		theGrid.new_food();
		theGrid.place_food();
	}
	else {
		// Clear the board to remove the snake from last iteration
		theGrid.reset();
		// Place the new snake location and food
		theSnake.add_head(next_move);
		theSnake.remove_tail();
		theGrid.place_snake(theSnake);
		theGrid.place_food();
	}
	return;
}

void draw_scorecard(SDL_Renderer* renderer) {
	SDL_SetRenderDrawColor(renderer, 233, 233, 233, 255);	// Grey
		// Create Rectangle
	SDL_Rect rect;
	rect.x = 0;
	rect.y = 0;
	rect.w = 200;
	rect.h = 600;
	SDL_RenderFillRect(renderer, &rect);
	return;
}

void draw_game(SDL_Renderer* renderer, grid theGrid) {
	// 601x601 pixel area for the 40x40 grid
	// 40 tiles 14x14 with 1 pixel space bordering each (40x14+41=601)

	int scorecardOffset = 201;	// 200 pixel scorecard + 1 pixel border
	for (int i = 0; i < GRID_HEIGHT; i++) {
		for (int j = 0; j < GRID_WIDTH; j++) {
			if (theGrid.a[i][j] == FOOD) {
				SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);	// Red
				SDL_Rect rect;
				rect.x = (j * 13) + (j * 2) + scorecardOffset;
				rect.y = (i * 13) + (i * 2) + 1;
				rect.w = 14;
				rect.h = 14;
				SDL_RenderFillRect(renderer, &rect);
			}
			else if (theGrid.a[i][j] == SNAKE) {
				SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);	// White
				SDL_Rect rect;
				rect.x = (j * 13) + (j * 2) + scorecardOffset;
				rect.y = (i * 13) + (i * 2) + 1;
				rect.w = 14;
				rect.h = 14;
				SDL_RenderFillRect(renderer, &rect);
			}
		}
	}
}

int main(int argc, char *argv[]) {

	// Create the SDL window and renderer
	SDL_Init(SDL_INIT_EVERYTHING);
	SDL_Window *window = SDL_CreateWindow("Snake", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 801, 601, SDL_WINDOW_SHOWN);
	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);

	// Create snake and grid objects
	grid theGrid;
	theGrid.new_food();
	snake theSnake;
	
	srand(2);

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
			if (event.type == SDL_KEYDOWN) {
				switch (event.key.keysym.sym) {
					case SDLK_LEFT:
						if (theSnake.oldDirection != directions::RIGHT) {	// prevent the snake from backing into itself
							newDirection = directions::LEFT;
						}
						break;
					case SDLK_RIGHT:
						if (theSnake.oldDirection != directions::LEFT) {
							newDirection = directions::RIGHT;
						}
						break;
					case SDLK_UP:
						if (theSnake.oldDirection != directions::DOWN) {
							newDirection = directions::UP;
						}
						break;
					case SDLK_DOWN:
						if (theSnake.oldDirection != directions::UP) {
							newDirection = directions::DOWN;
						}
						break;
					default:
						break;
				}
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
		theSnake.oldDirection = newDirection;	// Update the old direction

		// (3) Clear and Draw the Screen
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);	// Black
		SDL_RenderClear(renderer);

		draw_game(renderer, theGrid);
		draw_scorecard(renderer);

		SDL_RenderPresent(renderer);
		SDL_Delay(100);
	}

	return 0;
}